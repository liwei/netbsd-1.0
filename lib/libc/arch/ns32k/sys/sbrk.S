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
 *	$Id: sbrk.S,v 1.4 1994/06/10 22:46:16 phil Exp $
 */

#include "SYS.h"

	.data
	.globl	_end
	.globl	_curbrk; .type _curbrk, @object; .size _curbrk, 4
	.globl	minbrk; .type minbrk, @object; .size minbrk, 4
_curbrk:	.long	_end
minbrk:		.long	_end

	.text

ENTRY(sbrk)
	PIC_PROLOGUE
	addd	PIC_GOT(_curbrk), PIC_S_ARG0
	PIC_EPILOGUE
	movd	SYS_break, r0
	SVC
	bcs	cerror
	PIC_PROLOGUE
	movd	PIC_GOT(_curbrk), r0
	movd	PIC_S_ARG0, PIC_GOT(_curbrk)	/* XXX check this b */
	PIC_EPILOGUE
	ret	0
