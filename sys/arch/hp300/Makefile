#	from: @(#)Makefile	7.3 (Berkeley) 6/9/91
#	$Id: Makefile,v 1.3 1994/04/27 06:23:02 hpeyerl Exp $

COMM=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../netiso/*.[ch] ../netccitt/*.[ch] \
	../kern/*.c ../ufs/*.[ch] ../nfs/*.[ch] ../vm/*.[ch] ../sys/*.h

# Makefile for hp300 tags file

SUBDIR= stand

THP300=	../hp300/tags
SHP300=	../hp300/hp300/*.[ch] ../hp300/include/*.h \
	../hp300/hpux/*.[ch] ../hp300/dev/*.[ch]
AHP300=	../hp300/hp300/*.s

# Directories in which to place hp300 tags links
DHP300=	dev hpux include

tags:
	-ctags -dtf ${THP300} ${COMM} ${SHP300}
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AHP300} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> ${THP300}
	sort -o ${THP300} ${THP300}

links:
	-for i in ${DHP300}; do \
	    cd ../$$i && rm -f tags; ln -s ../tags tags; done

.include <bsd.prog.mk>
