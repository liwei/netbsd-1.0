/*	$NetBSD: cons.c,v 1.18 1994/06/29 06:31:32 cgd Exp $	*/

/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: Utah $Hdr: cons.c 1.7 92/01/21$
 *
 *	@(#)cons.c	8.2 (Berkeley) 1/12/94
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/vnode.h>

#include <dev/cons.h>

extern struct consdev constab[];

struct	tty *constty = NULL;	/* virtual console output device */
struct	consdev *cn_tab;	/* physical console device info */
struct	vnode *cn_devvp;	/* vnode for underlying device. */


void
cninit()
{
	register struct consdev *cp;

	/*
	 * Collect information about all possible consoles
	 * and find the one with highest priority
	 */
	for (cp = constab; cp->cn_probe; cp++) {
		(*cp->cn_probe)(cp);
		if (cp->cn_pri > CN_DEAD &&
		    (cn_tab == NULL || cp->cn_pri > cn_tab->cn_pri))
			cn_tab = cp;
	}
	/*
	 * No console, we can handle it
	 */
	if ((cp = cn_tab) == NULL)
		return;
	/*
	 * Turn on console
	 */
	(*cp->cn_init)(cp);
}

int
cnopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	if (cn_tab == NULL)
		return (0);

	/*
	 * always open the 'real' console device, so we don't get nailed
	 * later.  This follows normal device semantics; they always get
	 * open() calls.
	 */
	dev = cn_tab->cn_dev;
	if (cn_devvp == NULLVP) {
		/* try to get a reference on its vnode, but fail silently */
		cdevvp(dev, &cn_devvp);
	}
	return ((*cdevsw[major(dev)].d_open)(dev, flag, mode, p));
}
 
int
cnclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	struct vnode *vp;

	if (cn_tab == NULL)
		return (0);

	/*
	 * If the real console isn't otherwise open, close it.
	 * If it's otherwise open, don't close it, because that'll
	 * screw up others who have it open.
	 */
	dev = cn_tab->cn_dev;
	if (cn_devvp != NULLVP) {
		/* release our reference to real dev's vnode */
		vrele(cn_devvp);
		cn_devvp = NULLVP;
	}
	if (vfinddev(dev, VCHR, &vp) && vcount(vp))
		return (0);
	return ((*cdevsw[major(dev)].d_close)(dev, flag, mode, p));
}
 
int
cnread(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	/*
	 * If we would redirect input, punt.  This will keep strange
	 * things from happening to people who are using the real
	 * console.  Nothing should be using /dev/console for
	 * input (except a shell in single-user mode, but then,
	 * one wouldn't TIOCCONS then).
	 */
	if (constty != NULL && (cn_tab == NULL || cn_tab->cn_pri != CN_REMOTE))
		return 0;
	else if (cn_tab == NULL)
		return ENXIO;

	dev = cn_tab->cn_dev;
	return ((*cdevsw[major(dev)].d_read)(dev, uio, flag));
}
 
int
cnwrite(dev, uio, flag)
	dev_t dev;
	struct uio *uio;
{
	/*
	 * Redirect output, if that's appropriate.
	 * If there's no real console, return ENXIO.
	 */
	if (constty != NULL && (cn_tab == NULL || cn_tab->cn_pri != CN_REMOTE))
		dev = constty->t_dev;
	else if (cn_tab == NULL)
		return ENXIO;
	else
		dev = cn_tab->cn_dev;
	return ((*cdevsw[major(dev)].d_write)(dev, uio, flag));
}
 
int
cnioctl(dev, cmd, data, flag, p)
	dev_t dev;
	caddr_t data;
	struct proc *p;
{
	int error;

	/*
	 * Superuser can always use this to wrest control of console
	 * output from the "virtual" console.
	 */
	if (cmd == TIOCCONS && constty != NULL) {
		error = suser(p->p_ucred, (u_short *) NULL);
		if (error)
			return (error);
		constty = NULL;
		return (0);
	}

	/*
	 * Redirect the ioctl, if that's appropriate.
	 * Note that strange things can happen, if a program does
	 * ioctls on /dev/console, then the console is redirected
	 * out from under it.
	 */
	if (constty != NULL && (cn_tab == NULL || cn_tab->cn_pri != CN_REMOTE))
		dev = constty->t_dev;
	else if (cn_tab == NULL)
		return ENXIO;
	else
		dev = cn_tab->cn_dev;
	return ((*cdevsw[major(dev)].d_ioctl)(dev, cmd, data, flag, p));
}

/*ARGSUSED*/
int
cnselect(dev, rw, p)
	dev_t dev;
	int rw;
	struct proc *p;
{
	/*
	 * Redirect the ioctl, if that's appropriate.
	 * I don't want to think of the possible side effects
	 * of console redirection here.
	 */
	if (constty != NULL && (cn_tab == NULL || cn_tab->cn_pri != CN_REMOTE))
		dev = constty->t_dev;
	else if (cn_tab == NULL)
		return ENXIO;
	else
		dev = cn_tab->cn_dev;
	return (ttselect(cn_tab->cn_dev, rw, p));
}

int
cngetc()
{
	if (cn_tab == NULL)
		return (0);
	return ((*cn_tab->cn_getc)(cn_tab->cn_dev));
}

int
cnputc(c)
	register int c;
{
	if (cn_tab == NULL)
		return;
	if (c) {
		(*cn_tab->cn_putc)(cn_tab->cn_dev, c);
		if (c == '\n')
			(*cn_tab->cn_putc)(cn_tab->cn_dev, '\r');
	}
}
