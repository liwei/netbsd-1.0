#	from: @(#)Makefile	5.8 (Berkeley) 6/5/90
#	$Id: Makefile,v 1.2 1993/07/30 22:30:17 mycroft Exp $

PROG=	vfontedpr
SRCS=	regexp.c vfontedpr.c vgrindefs.c
MAN1=	vgrind.0
MAN5=	vgrindefs.0
BINDIR=	/usr/libexec

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/vgrind.sh ${DESTDIR}/usr/bin/vgrind
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/vgrindefs.src \
	    ${DESTDIR}/usr/share/misc/vgrindefs
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/tmac.vgrind \
	    ${DESTDIR}/usr/share/tmac

.include <bsd.prog.mk>
