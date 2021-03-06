/*-
 * Copyright (c) 1994 Charles Hannum.
 * Copyright (c) 1992, 1993 Erik Forsberg.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL I BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	$Id: pms.c,v 1.9.2.2 1994/07/19 17:01:52 cgd Exp $
 */

/*
 * XXXX
 * This is a hack.  This driver should really be combined with the
 * keyboard driver, since they go through the same buffer and use the
 * same I/O ports.  Frobbing the mouse and keyboard at the same time
 * may result in dropped characters and/or corrupted mouse events.
 */

#include "pms.h"
#if NPMS > 1
#error Only one PS/2 style mouse may be configured into your system.
#endif

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/select.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/device.h>

#include <machine/cpu.h>
#include <machine/pio.h>
#include <machine/mouse.h>

#include <i386/isa/isavar.h>

#define	PMS_DATA	0       /* offset for data port, read-write */
#define	PMS_CNTRL	4       /* offset for control port, write-only */
#define	PMS_STATUS	4	/* offset for status port, read-only */
#define	PMS_NPORTS	8

/* status bits */
#define	PMS_OBUF_FULL	0x01
#define	PMS_IBUF_FULL	0x02

/* controller commands */
#define	PMS_INT_ENABLE	0x47	/* enable controller interrupts */
#define	PMS_INT_DISABLE	0x65	/* disable controller interrupts */
#define	PMS_AUX_ENABLE	0xa7	/* enable auxiliary port */
#define	PMS_AUX_DISABLE	0xa8	/* disable auxiliary port */
#define	PMS_MAGIC_1	0xa9	/* XXX */
#define	PMS_MAGIC_2	0xaa	/* XXX */

#define	PMS_8042_CMD	0x65

/* mouse commands */
#define	PMS_SET_SCALE11	0xe6	/* set scaling 1:1 */
#define	PMS_SET_SCALE21 0xe7	/* set scaling 2:1 */
#define	PMS_SET_RES	0xe8	/* set resolution */
#define	PMS_GET_SCALE	0xe9	/* get scaling factor */
#define	PMS_SET_STREAM	0xea	/* set streaming mode */
#define	PMS_SET_SAMPLE	0xf3	/* set sampling rate */
#define	PMS_DEV_ENABLE	0xf4	/* mouse on */
#define	PMS_DEV_DISABLE	0xf5	/* mouse off */
#define	PMS_RESET	0xff	/* reset */

#define	PMS_CHUNK	128	/* chunk size for read */
#define	PMS_BSIZE	1020	/* buffer size */

struct pms_softc {		/* driver status information */
	struct device sc_dev;
	struct intrhand sc_ih;

	struct clist sc_q;
	struct selinfo sc_rsel;
	u_short sc_iobase;	/* I/O port base */
	u_char sc_state;	/* mouse driver state */
#define	PMS_OPEN	0x01	/* device is open */
#define	PMS_ASLP	0x02	/* waiting for mouse data */
	u_char sc_status;	/* mouse button status */
	int sc_x, sc_y;		/* accumulated motion in the X,Y axis */
};

int pmsprobe();
void pmsattach();
int pmsintr __P((struct pms_softc *));

struct cfdriver pmscd = {\
	NULL, "pms", pmsprobe, pmsattach, DV_TTY, sizeof(struct pms_softc)
};

#define	PMSUNIT(dev)	(minor(dev))

static inline void
pms_flush(iobase)
	u_short iobase;
{
	u_char c;
	while (c = inb(iobase+PMS_STATUS) & 0x03)
		if ((c & PMS_OBUF_FULL) == PMS_OBUF_FULL) {
			/* XXX - delay is needed to prevent some keyboards from
			   wedging when the system boots */
			delay(6);
			(void) inb(iobase+PMS_DATA);
		}
}

static inline void
pms_dev_cmd(iobase, value)
	u_short iobase;
	u_char value;
{
	pms_flush(iobase);
	outb(iobase+PMS_CNTRL, 0xd4);
	pms_flush(iobase);
	outb(iobase+PMS_DATA, value);
}

static inline void
pms_aux_cmd(iobase, value)
	u_short iobase;
	u_char value;
{
	pms_flush(iobase);
	outb(iobase+PMS_CNTRL, value);
}

static inline void
pms_pit_cmd(iobase, value)
	u_short iobase;
	u_char value;
{
	pms_flush(iobase);
	outb(iobase+PMS_CNTRL, 0x60);
	pms_flush(iobase);
	outb(iobase+PMS_DATA, value);
}

int
pmsprobe(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct isa_attach_args *ia = aux;
	u_short iobase = ia->ia_iobase;
	u_char x;

	pms_dev_cmd(iobase, PMS_RESET);
	pms_aux_cmd(iobase, PMS_MAGIC_1);
	pms_aux_cmd(iobase, PMS_MAGIC_2);
	x = inb(iobase+PMS_DATA);
	pms_pit_cmd(iobase, PMS_INT_DISABLE);
	if (x & 0x04)
		return 0;

	ia->ia_iosize = PMS_NPORTS;
	ia->ia_msize = 0;
	return 1;
}

void
pmsattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct pms_softc *sc = (void *)self;
	struct isa_attach_args *ia = aux;
	u_short iobase = ia->ia_iobase;

	printf("\n");

	/* Other initialization was done by pmsprobe. */
	sc->sc_iobase = iobase;
	sc->sc_state = 0;

	sc->sc_ih.ih_fun = pmsintr;
	sc->sc_ih.ih_arg = sc;
	sc->sc_ih.ih_level = IPL_NONE;
	intr_establish(ia->ia_irq, &sc->sc_ih);
}

int
pmsopen(dev, flag)
	dev_t dev;
	int flag;
{
	int unit = PMSUNIT(dev);
	struct pms_softc *sc;

	if (unit >= pmscd.cd_ndevs)
		return ENXIO;
	sc = pmscd.cd_devs[unit];
	if (!sc)
		return ENXIO;

	if (sc->sc_state & PMS_OPEN)
		return EBUSY;

	if (clalloc(&sc->sc_q, PMS_BSIZE, 0) == -1)
		return ENOMEM;

	sc->sc_state |= PMS_OPEN;
	sc->sc_status = 0;
	sc->sc_x = sc->sc_y = 0;

	/* Enable interrupts. */
	pms_dev_cmd(sc->sc_iobase, PMS_DEV_ENABLE);
	pms_aux_cmd(sc->sc_iobase, PMS_AUX_ENABLE);
#if 0
	pms_dev_cmd(sc->sc_iobase, PMS_SET_RES);
	pms_dev_cmd(sc->sc_iobase, 3);		/* 8 counts/mm */
	pms_dev_cmd(sc->sc_iobase, PMS_SET_SCALE21);
	pms_dev_cmd(sc->sc_iobase, PMS_SET_SAMPLE);
	pms_dev_cmd(sc->sc_iobase, 100);	/* 100 samples/sec */
	pms_dev_cmd(sc->sc_iobase, PMS_SET_STREAM);
#endif
	pms_pit_cmd(sc->sc_iobase, PMS_INT_ENABLE);

	return 0;
}

int
pmsclose(dev, flag)
	dev_t dev;
	int flag;
{
	struct pms_softc *sc = pmscd.cd_devs[PMSUNIT(dev)];

	/* Disable interrupts. */
	pms_dev_cmd(sc->sc_iobase, PMS_DEV_DISABLE);
	pms_pit_cmd(sc->sc_iobase, PMS_INT_DISABLE);
	pms_aux_cmd(sc->sc_iobase, PMS_AUX_DISABLE);

	sc->sc_state &= ~PMS_OPEN;

	clfree(&sc->sc_q);

	return 0;
}

int
pmsread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
	int flag;
{
	struct pms_softc *sc = pmscd.cd_devs[PMSUNIT(dev)];
	int s;
	int error;
	size_t length;
	u_char buffer[PMS_CHUNK];

	/* Block until mouse activity occured. */

	s = spltty();
	while (sc->sc_q.c_cc == 0) {
		if (flag & IO_NDELAY) {
			splx(s);
			return EWOULDBLOCK;
		}
		sc->sc_state |= PMS_ASLP;
		if (error = tsleep((caddr_t)sc, PZERO | PCATCH, "pmsrea", 0)) {
			sc->sc_state &= ~PMS_ASLP;
			splx(s);
			return error;
		}
	}
	splx(s);

	/* Transfer as many chunks as possible. */

	while (sc->sc_q.c_cc > 0 && uio->uio_resid > 0) {
		length = min(sc->sc_q.c_cc, uio->uio_resid);
		if (length > sizeof(buffer))
			length = sizeof(buffer);

		/* Remove a small chunk from the input queue. */
		(void) q_to_b(&sc->sc_q, buffer, length);

		/* Copy the data to the user process. */
		if (error = uiomove(buffer, length, uio))
			break;
	}

	return error;
}

int
pmsioctl(dev, cmd, addr, flag)
	dev_t dev;
	int cmd;
	caddr_t addr;
	int flag;
{
	struct pms_softc *sc = pmscd.cd_devs[PMSUNIT(dev)];
	struct mouseinfo info;
	int s;
	int error;

	switch (cmd) {
	case MOUSEIOCREAD:
		s = spltty();

		info.status = sc->sc_status;
		if (sc->sc_x || sc->sc_y)
			info.status |= MOVEMENT;

		if (sc->sc_x > 127)
			info.xmotion = 127;
		else if (sc->sc_x < -127)
			/* Bounding at -127 avoids a bug in XFree86. */
			info.xmotion = -127;
		else
			info.xmotion = sc->sc_x;

		if (sc->sc_y > 127)
			info.ymotion = 127;
		else if (sc->sc_y < -127)
			info.ymotion = -127;
		else
			info.ymotion = sc->sc_y;

		/* Reset historical information. */
		sc->sc_x = sc->sc_y = 0;
		sc->sc_status &= ~BUTCHNGMASK;
		ndflush(&sc->sc_q, sc->sc_q.c_cc);

		splx(s);
		error = copyout(&info, addr, sizeof(struct mouseinfo));
		break;

	default:
		error = EINVAL;
		break;
	}

	return error;
}

/* Masks for the first byte of a packet */
#define PS2LBUTMASK 0x01
#define PS2RBUTMASK 0x02
#define PS2MBUTMASK 0x04

int
pmsintr(sc)
	struct pms_softc *sc;
{
	u_short iobase = sc->sc_iobase;
	static int state = 0;
	static u_char buttons;
	u_char changed;
	static char dx, dy;
	u_char buffer[5];

	if ((sc->sc_state & PMS_OPEN) == 0) {
		/* Interrupts are not expected.  Discard the byte. */
		(void) inb(iobase + PMS_DATA);
		return 0;
	}

	switch (state) {

	case 0:
		buttons = inb(iobase + PMS_DATA);
		if ((buttons & 0xc0) == 0)
			++state;
		break;

	case 1:
		dx = inb(iobase + PMS_DATA);
		/* Bounding at -127 avoids a bug in XFree86. */
		dx = (dx == -128) ? -127 : dx;
		++state;
		break;

	case 2:
		dy = inb(iobase + PMS_DATA);
		dy = (dy == -128) ? -127 : dy;
		state = 0;

		buttons = ((buttons & PS2LBUTMASK) << 2) |
			  ((buttons & (PS2RBUTMASK | PS2MBUTMASK)) >> 1);
		changed = ((buttons ^ sc->sc_status) & BUTSTATMASK) << 3;
		sc->sc_status = buttons | (sc->sc_status & ~BUTSTATMASK) | changed;

		if (dx || dy || changed) {
			/* Update accumulated movements. */
			sc->sc_x += dx;
			sc->sc_y += dy;

			/* Add this event to the queue. */
			buffer[0] = 0x80 | (buttons ^ BUTSTATMASK);
			buffer[1] = dx;
			buffer[2] = dy;
			buffer[3] = buffer[4] = 0;
			(void) b_to_q(buffer, sizeof buffer, &sc->sc_q);

			if (sc->sc_state & PMS_ASLP) {
				sc->sc_state &= ~PMS_ASLP;
				wakeup((caddr_t)sc);
			}
			selwakeup(&sc->sc_rsel);
		}

		break;
	}

	return -1;
}

int
pmsselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{
	struct pms_softc *sc = pmscd.cd_devs[PMSUNIT(dev)];
	int s;
	int ret;

	if (rw == FWRITE)
		return 0;

	s = spltty();
	if (!sc->sc_q.c_cc) {
		selrecord(p, &sc->sc_rsel);
		ret = 0;
	} else
		ret = 1;
	splx(s);

	return ret;
}
