# bootpef/Makefile
# $Id: Makefile,v 1.2 1994/06/27 21:31:21 gwr Exp $

PROG=	bootpef
SRCDIR= ${.CURDIR}/../bootpd
CFLAGS+= -DETC_ETHERS -DDEBUG -I${SRCDIR}
.PATH: ${SRCDIR}

SRCS=	bootpef.c dovend.c readfile.c hash.c dumptab.c \
	 lookup.c hwaddr.c report.c tzone.c

MAN8=	bootpef.0

.include <bsd.prog.mk>

