#include "DEFS.h"

ENTRY(swab)
	movl	sp@(4),a0	/* source */
	movl	sp@(8),a1	/* destination */
	movl	sp@(12),d0	/* count */
	jeq	swdone

swloop:
	movw	a0@+,d1
	rorw	#8,d1
	movw	d1,a1@+
	subql	#1,d0
	jne	swloop

swdone:
	rts
