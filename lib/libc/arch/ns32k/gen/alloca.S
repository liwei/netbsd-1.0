/* 
 * Copyright (c) 1992 Helsinki University of Technology
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * HELSINKI UNIVERSITY OF TECHNOLOGY ALLOWS FREE USE OF THIS SOFTWARE IN
 * ITS "AS IS" CONDITION. HELSINKI UNIVERSITY OF TECHNOLOGY DISCLAIMS ANY
 * LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE
 * USE OF THIS SOFTWARE.
 */
/*
 * HISTORY
 * 29-Apr-92  Johannes Helander (jvh) at Helsinki University of Technology
 *	Created.
 *
 * 	$Id: alloca.S,v 1.1 1993/10/07 00:20:15 cgd Exp $
 */
/*
 * Note: Saved registers are accessed through the frame pointer so 
 * no special magic is required here.
 */

#include <machine/asm.h>

ENTRY(alloca)
	movd	tos,r2		/* get return address */
	movd	tos,r1		/* get length */
	sprd	sp,r0
	subd	r1,r0
	lprd	sp,r0
	movd	r1,tos
	jump	0(r2)
