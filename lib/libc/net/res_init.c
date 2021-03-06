/*-
 * Copyright (c) 1985, 1989 Regents of the University of California.
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
 */

#if defined(LIBC_SCCS) && !defined(lint)
/*static char *sccsid = "from: @(#)res_init.c	6.15 (Berkeley) 2/24/91";*/
static char *rcsid = "$Id: res_init.c,v 1.5 1994/04/07 07:00:19 deraadt Exp $";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void res_setoptions __P((char *, char *));
static u_long net_mask __P((struct in_addr));

/*
 * Resolver state default settings
 */

struct __res_state _res = {
	RES_TIMEOUT,               	/* retransmition time interval */
	4,                         	/* number of times to retransmit */
	RES_DEFAULT,			/* options flags */
	1,                         	/* number of name servers */
};

/*
 * Set up default settings.  If the configuration file exist, the values
 * there will have precedence.  Otherwise, the server address is set to
 * INADDR_ANY and the default domain name comes from the gethostname().
 *
 * The configuration file should only be used if you want to redefine your
 * domain or run without a server on your machine.
 *
 * Return 0 if completes successfully, -1 on error
 */
res_init()
{
	register FILE *fp;
	register char *cp, **pp, *net;
	register int n;
	char buf[BUFSIZ], buf2[BUFSIZ];
	int nserv = 0;    /* number of nameserver records read from file */
	int haveenv = 0;
	int havesearch = 0;
	int nsort = 0;
	u_long mask;

	_res.nsaddr.sin_addr.s_addr = INADDR_ANY;
	_res.nsaddr.sin_family = AF_INET;
	_res.nsaddr.sin_port = htons(NAMESERVER_PORT);
	_res.nscount = 1;
	_res.ndots = 1;
	_res.pfcode = 0;
	strncpy(_res.lookups, "f", sizeof _res.lookups);

	/* Allow user to override the local domain definition */
	if ((cp = getenv("LOCALDOMAIN")) != NULL) {
		(void)strncpy(_res.defdname, cp, sizeof(_res.defdname) - 1);
		haveenv++;

		/*
		 * Set search list to be blank-separated strings
		 * from rest of env value.  Permits users of LOCALDOMAIN
		 * to still have a search list, and anyone to set the
		 * one that they want to use as an individual (even more
		 * important now that the rfc1535 stuff restricts searches)
		 */
		cp = _res.defdname;
		pp = _res.dnsrch;
		*pp++ = cp;
		for (n = 0; *cp && pp < _res.dnsrch + MAXDNSRCH; cp++) {
			if (*cp == '\n')        /* silly backwards compat */
				break;
			else if (*cp == ' ' || *cp == '\t') {
				*cp = 0;
				n = 1;
			} else if (n) {
				*pp++ = cp;
				n = 0;
				havesearch = 1;
			}
		}
		/* null terminate last domain if there are excess */
		while (*cp != '\0' && *cp != ' ' && *cp != '\t' && *cp != '\n')
			cp++;
		*cp = '\0';
		*pp++ = 0;
	}

	if ((fp = fopen(_PATH_RESCONF, "r")) != NULL) {
	    strncpy(_res.lookups, "bf", sizeof _res.lookups);

	    /* read the config file */
	    while (fgets(buf, sizeof(buf), fp) != NULL) {
		/* skip comments */
		if ((*buf == ';') || (*buf == '#'))
			continue;
		/* read default domain name */
		if (!strncmp(buf, "domain", sizeof("domain") - 1)) {
		    if (haveenv)	/* skip if have from environ */
			    continue;
		    cp = buf + sizeof("domain") - 1;
		    while (*cp == ' ' || *cp == '\t')
			    cp++;
		    if ((*cp == '\0') || (*cp == '\n'))
			    continue;
		    (void)strncpy(_res.defdname, cp, sizeof(_res.defdname) - 1);
		    if ((cp = strpbrk(_res.defdname, "\t\n")) != NULL)
			    *cp = '\0';
		    havesearch = 0;
		    continue;
		}
		/* lookup types */
		if (!strncmp(buf, "lookup", sizeof("lookup") -1)) {
		    char *sp = NULL;

		    bzero(_res.lookups, sizeof _res.lookups);
		    cp = buf + sizeof("lookup") - 1;
		    for (n = 0;; cp++) {
		    	    if (n == MAXDNSLUS)
				    break;
			    if ((*cp == '\0') || (*cp == '\n')) {
				    if (sp) {
					    if (*sp=='y' || *sp=='b' || *sp=='f')
						    _res.lookups[n++] = *sp;
					    sp = NULL;
				    }
				    break;
			    } else if ((*cp == ' ') || (*cp == '\t') || (*cp == ',')) {
				    if (sp) {
					    if (*sp=='y' || *sp=='b' || *sp=='f')
						    _res.lookups[n++] = *sp;
					    sp = NULL;
				    }
			    } else if (sp == NULL)
				    sp = cp;
		    }
		    continue;
		}
		/* set search list */
		if (!strncmp(buf, "search", sizeof("search") - 1)) {
		    if (haveenv)	/* skip if have from environ */
			    continue;
		    cp = buf + sizeof("search") - 1;
		    while (*cp == ' ' || *cp == '\t')
			    cp++;
		    if ((*cp == '\0') || (*cp == '\n'))
			    continue;
		    (void)strncpy(_res.defdname, cp, sizeof(_res.defdname) - 1);
		    if ((cp = strchr(_res.defdname, '\n')) != NULL)
			    *cp = '\0';
		    /*
		     * Set search list to be blank-separated strings
		     * on rest of line.
		     */
		    cp = _res.defdname;
		    pp = _res.dnsrch;
		    *pp++ = cp;
		    for (n = 0; *cp && pp < _res.dnsrch + MAXDNSRCH; cp++) {
			    if (*cp == ' ' || *cp == '\t') {
				    *cp = 0;
				    n = 1;
			    } else if (n) {
				    *pp++ = cp;
				    n = 0;
			    }
		    }
		    /* null terminate last domain if there are excess */
		    while (*cp != '\0' && *cp != ' ' && *cp != '\t')
			    cp++;
		    *cp = '\0';
		    *pp++ = 0;
		    havesearch = 1;
		    continue;
		}
		/* read nameservers to query */
		if (!strncmp(buf, "nameserver", sizeof("nameserver") - 1) &&
		   nserv < MAXNS) {
		    struct in_addr a;

		    cp = buf + sizeof("nameserver") - 1;
		    while (*cp == ' ' || *cp == '\t')
			    cp++;
		    if ((*cp != '\0') && (*cp != '\n') && inet_aton(cp, &a)) {
			_res.nsaddr_list[nserv].sin_addr = a;
			_res.nsaddr_list[nserv].sin_family = AF_INET;
			_res.nsaddr_list[nserv].sin_port =
			    htons(NAMESERVER_PORT);
			nserv++;
		    }
		    continue;
		}
		if (!strncmp(buf, "sortlist", sizeof("sortlist") - 1)) {
		    struct in_addr a;

		    cp = buf + sizeof("sortlist") - 1;
		    while (*cp == ' ' || *cp == '\t')
			cp++;
		    while (sscanf(cp,"%[0-9./]s", buf2) && nsort < MAXRESOLVSORT) {
			if (net = strchr(buf2, '/'))
			    *net = '\0';
			if (inet_aton(buf2, &a)) {
			    _res.sort_list[nsort].addr = a;
			    if (net && inet_aton(net+1, &a)) {
				_res.sort_list[nsort].mask = a.s_addr;
			    } else {
				_res.sort_list[nsort].mask =
					net_mask(_res.sort_list[nsort].addr);
			    }
			    nsort++;
			}
			if (net)
				*net = '/';
			cp += strlen(buf2);
			while (*cp == ' ' || *cp == '\t')
			    cp++;
		    }
		    continue;
		}
		if (!strncmp(buf, "options", sizeof("options") -1)) {
		    res_setoptions(buf + sizeof("options") - 1, "conf");
		    continue;
		}
	    }
	    if (nserv > 1) 
		_res.nscount = nserv;
	    _res.nsort = nsort;
	    (void) fclose(fp);
	}
	if (_res.defdname[0] == 0) {
		if (gethostname(buf, sizeof(_res.defdname) - 1) == 0 &&
		   (cp = strchr(buf, '.')))
			(void)strcpy(_res.defdname, cp + 1);
	}

	/* find components of local domain that might be searched */
	if (havesearch == 0) {
		pp = _res.dnsrch;
		*pp++ = _res.defdname;
		*pp = NULL;
	}

	if ((cp = getenv("RES_OPTIONS")) != NULL)
		res_setoptions(cp, "env");
	_res.options |= RES_INIT;
	return (0);
}

static void
res_setoptions(options, source)
	char *options, *source;
{
	char *cp = options;
	int i;

#ifdef DEBUG
	if (_res.options & RES_DEBUG) {
		printf(";; res_setoptions(\"%s\", \"%s\")...\n",
		       options, source);
	}
#endif
	while (*cp) {
		/* skip leading and inner runs of spaces */
		while (*cp == ' ' || *cp == '\t')
			cp++;
		/* search for and process individual options */
		if (!strncmp(cp, "ndots:", sizeof("ndots:")-1)) {
			i = atoi(cp + sizeof("ndots:") - 1);
			if (i <= RES_MAXNDOTS)
				_res.ndots = i;
			else
				_res.ndots = RES_MAXNDOTS;
#ifdef DEBUG
			if (_res.options & RES_DEBUG) {
				printf(";;\tndots=%d\n", _res.ndots);
			}
#endif
		} else if (!strncmp(cp, "debug", sizeof("debug")-1)) {
#ifdef DEBUG
			if (!(_res.options & RES_DEBUG)) {
				printf(";; res_setoptions(\"%s\", \"%s\")..\n",
				       options, source);
				_res.options |= RES_DEBUG;
			}
			printf(";;\tdebug\n");
#endif
		} else {
			/* XXX - print a warning here? */
		}
		/* skip to next run of spaces */
		while (*cp && *cp != ' ' && *cp != '\t')
			cp++;
	}
}

static u_long
net_mask(in)		/* XXX - should really use system's version of this */
	struct in_addr in;
{
	register u_long i = ntohl(in.s_addr);

	if (IN_CLASSA(i))
		return (htonl(IN_CLASSA_NET));
	if (IN_CLASSB(i))
		return (htonl(IN_CLASSB_NET));
	return (htonl(IN_CLASSC_NET));
}
