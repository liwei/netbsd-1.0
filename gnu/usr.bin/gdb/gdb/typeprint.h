/* Language independent support for printing types for GDB, the GNU debugger.
   Copyright 1986, 1988, 1989, 1991, 1992, 1993 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	$Id: typeprint.h,v 1.1 1994/01/28 12:41:05 pk Exp $
*/

void
print_type_scalar PARAMS ((struct type *type, LONGEST, FILE *));
