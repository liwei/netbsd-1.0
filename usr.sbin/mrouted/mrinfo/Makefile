#	from: Id: Makefile,v 1.5 1993/06/24 05:11:16 deering Exp
#	$Id: Makefile,v 1.2 1994/01/14 19:44:54 cgd Exp $

.PATH: ${.CURDIR}/..
CFLAGS+= -I${.CURDIR}/..

PROG=	mrinfo
SRCS=	igmp.c inet.c kern.c mrinfo.c
NOMAN=	noman

.include "../../Makefile.inc"
.include <bsd.prog.mk>
