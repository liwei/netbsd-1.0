#	from: @(#)Makefile	8.1 (Berkeley) 5/31/93
#	$Id: Makefile,v 1.3 1994/05/12 17:39:26 jtc Exp $

PROG=	mille
SRCS=	comp.c end.c extern.c init.c mille.c misc.c move.c print.c \
	roll.c save.c types.c varpush.c
DPADD=	${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lcurses -ltermlib -lcompat
MAN6=	mille.0
HIDEGAME=hidegame

.include <bsd.prog.mk>

