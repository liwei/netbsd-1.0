/*
 * Copyright (c) 1994 Winning Strategies, Inc.
 * All rights reserved.
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
 *      This product includes software developed by Winning Strategies, Inc.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char *rcsid = "$Id: nl_langinfo.c,v 1.1 1994/06/21 04:14:03 jtc Exp $";
#endif /* LIBC_SCCS and not lint */

#define _LOCALE_PRIVATE

#include <locale.h>
#include <nl_types.h>
#include <langinfo.h>

char *
nl_langinfo(item)
	nl_item item;
{
	const char *s;

	switch (item) {
	case D_T_FMT:
		s =  _CurrentTimeLocale->d_t_fmt;
		break;	
	case D_FMT:
		s =  _CurrentTimeLocale->d_fmt;
		break;
	case T_FMT:
		s =  _CurrentTimeLocale->t_fmt;
		break;
	case T_FMT_AMPM:
		s =  _CurrentTimeLocale->t_fmt_ampm;
		break;
	case AM_STR:
	case PM_STR:
		s =  _CurrentTimeLocale->am_pm[item - AM_STR];
		break;
	case DAY_1:
	case DAY_2:
	case DAY_3:
	case DAY_4:
	case DAY_5:
	case DAY_6:
	case DAY_7:
		s =  _CurrentTimeLocale->day[item - DAY_1];
		break;
	case ABDAY_1:
	case ABDAY_2:
	case ABDAY_3:
	case ABDAY_4:
	case ABDAY_5:
	case ABDAY_6:
	case ABDAY_7:
		s =  _CurrentTimeLocale->abday[item - ABDAY_1];
		break;
	case MON_1:
	case MON_2:
	case MON_3:
	case MON_4:
	case MON_5:
	case MON_6:
	case MON_7:
	case MON_8:
	case MON_9:
	case MON_10:
	case MON_11:
	case MON_12:
		s =  _CurrentTimeLocale->mon[item - MON_1];
		break;
	case ABMON_1:
	case ABMON_2:
	case ABMON_3:
	case ABMON_4:
	case ABMON_5:
	case ABMON_6:
	case ABMON_7:
	case ABMON_8:
	case ABMON_9:
	case ABMON_10:
	case ABMON_11:
	case ABMON_12:
		s =  _CurrentTimeLocale->abmon[item - ABMON_1];
		break;
	case RADIXCHAR:
		s =  _CurrentNumericLocale->decimal_point;
		break;
	case THOUSEP:
		s =  _CurrentNumericLocale->thousands_sep;
		break;
	case YESSTR:				/* XXX */
		s =  "yes";
		break;
	case YESEXPR:				/* XXX */
		s =  "^[yY]";
		break;
	case NOSTR:				/* XXX */
		s =  "no";
		break;
	case NOEXPR:				/* XXX */
		s =  "^[nN]";
		break;
	case CRNCYSTR:				/* XXX */
		s =  "";
		break;
	default:
		s =  "";
		break;
	}

	return (char *) s;
}
