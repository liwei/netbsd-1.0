/*
 * Copyright (c) 1992,1993,1994 Hellmuth Michaelis and Brian Dunford-Shore
 *
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
 *	This product includes software developed by
 *	Hellmuth Michaelis and Brian Dunford-Shore
 * 4. The name authors may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

static char *id =
	"@(#)loadfont.c, 3.00, Last Edit-Date: [Mon Jan 10 21:26:09 1994]";

/*---------------------------------------------------------------------------*
 *
 *	load a font into vga character font memory
 *
 *	-hm	removing explicit HGC support (same as MDA ..)
 *	-hm	new pcvt_ioctl.h SIZ_xxROWS
 *
 *---------------------------------------------------------------------------*/
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <machine/pcvt_ioctl.h>

#define FONT8X8		2048	/* filesize for 8x8 font              */
#define HEIGHT8X8	8	/* 8 scan lines char cell height      */
#define SSCAN8X8	143	/* 400 scan lines on screen - 256 - 1 */
#define SROWS8X8	50	/* 50 character lines on screen       */

#define FONT8X10	2560	/* filesize for 8x10 font             */
#define HEIGHT8X10	10	/* 10 scan lines char cell height     */
#define SSCAN8X10	143	/* 400 scan lines on screen - 256 - 1 */
#define SROWS8X10	40	/* 50 character lines on screen       */

#define FONT8X14	3584	/* filesize for 8x14 font             */
#define HEIGHT8X14	14	/* 14 scan lines char cell height     */
#define SSCAN8X14	135	/* 392 scan lines on screen - 256 - 1 */
#define SROWS8X14	28	/* 28 character lines on screen       */

#define FONT8X16	4096	/* filesize for 8x16 font             */
#define HEIGHT8X16	16	/* 16 scan lines char cell height     */
#define SSCAN8X16	143	/* 400 scan lines on screen - 256 - 1 */
#define SROWS8X16	25	/* 25 character lines on screen       */

struct screeninfo screeninfo;

main(argc,argv)
int argc;
char *argv[];
{
	extern int optind;
	extern int opterr;
	extern char *optarg;

	FILE *in;
	struct stat sbuf, *sbp;
	unsigned char *fonttab;
	int ret;
	int chr_height;
	int scr_scan;
	int scr_rows;
	int c;
	int chr_set = -1;
	char *filename;
	int fflag = -1;
	int info = -1;
	
	while( (c = getopt(argc, argv, "c:f:i")) != EOF)
	{
		switch(c)
		{
			case 'c':
				chr_set = atoi(optarg);
				break;
				
			case 'f':
				filename = optarg;
				fflag = 1;
				break;
				
			case 'i':
				info = 1;
				break;
				
			case '?':
			default:
				usage();
				break;
		}
	}
	
	if(chr_set == -1 || fflag == -1)
		info = 1;

	if(info == 1)
	{
		int i;
	
		if(ioctl(0, VGAGETSCREEN, &screeninfo) == -1)
		{
		    perror("ioctl VGAGETSCREEN failed");
		    exit(1);
		}

		switch(screeninfo.adaptor_type)
		{
		  case UNKNOWN_ADAPTOR:
		  case MDA_ADAPTOR:
		  case CGA_ADAPTOR:
		    printf("Adaptor does not support Downloadable Fonts!\n");
		    break;
		  case EGA_ADAPTOR:
		    printheader();
		    for(i = 0;i < 4;i++)
		    {
			printvgafontattr(i);
		    }
		    break;
		  case VGA_ADAPTOR:
		    printheader();		  
		    for(i = 0;i < 8;i++)
		    {
			printvgafontattr(i);
		    }
		}
		printf("\n");
		exit(0);
	}

	if(chr_set < 0 || chr_set > 7)
		usage();

	sbp = &sbuf;
	
	if((in = fopen(filename, "r")) == NULL)
	{
		char buffer[80];
		sprintf(buffer, "cannot open file %s for reading", filename);
		perror(buffer);
		exit(1);
	}

	if((fstat(fileno(in), sbp)) != 0)
	{
		char buffer[80];
		sprintf(buffer, "cannot fstat file %s", filename);
		perror(buffer);
		exit(1);
	}
		
	switch(sbp->st_size)
	{
		case FONT8X8:
			chr_height = HEIGHT8X8;
			scr_scan = SSCAN8X8;
			scr_rows = SIZ_50ROWS;
			break;
			
		case FONT8X10:
			chr_height = HEIGHT8X10;
			scr_scan = SSCAN8X10;
			scr_rows = SIZ_40ROWS;
			break;
			
		case FONT8X14:
			chr_height = HEIGHT8X14;
			scr_scan = SSCAN8X14;
			scr_rows = SIZ_28ROWS;
			break;
			
		case FONT8X16:
			chr_height = HEIGHT8X16;
			scr_scan = SSCAN8X16;
			scr_rows = SIZ_25ROWS;
			break;
			
		default:
			fprintf(stderr,"error, file %s is no valid font file, size=%d\n",argv[1],sbp->st_size);
			exit(1);
	}			

	if((fonttab = (unsigned char *)malloc((size_t)sbp->st_size)) == NULL)
	{
		fprintf(stderr,"error, malloc failed\n");
		exit(1);
	}

	if((ret = fread(fonttab, sizeof(*fonttab), sbp->st_size, in)) != sbp->st_size)
	{
		fprintf(stderr,"error reading file %s, size = %d, read =  is no valid font file, size=%d\n",argv[1],sbp->st_size, ret);
		exit(1);
	}		

	loadfont(chr_set, chr_height, fonttab);
	setfont(chr_set, 1, chr_height - 1, scr_scan, scr_rows);

	exit(0);
}

setfont(charset, fontloaded, charscan, scrscan, scrrow)
int charset, fontloaded, charscan, scrscan, scrrow;
{
	struct vgafontattr vfattr;

	vfattr.character_set = charset;
	vfattr.font_loaded = fontloaded;
	vfattr.character_scanlines = charscan;
	vfattr.screen_scanlines = scrscan;
	vfattr.screen_size = scrrow;

	if(ioctl(1, VGASETFONTATTR, &vfattr) == -1)
	{
		perror("loadfont - ioctl VGASETFONTATTR failed, error");
		exit(1);
	}
}

loadfont(fontset,charscanlines,font_table)
int fontset;
int charscanlines;
unsigned char *font_table;
{
	int i, j;
	struct vgaloadchar vlc;

	vlc.character_set = fontset;
	vlc.character_scanlines = charscanlines;

	for(i = 0; i < 256; i++)
	{
		vlc.character = i;
		for (j = 0; j < charscanlines; j++)
		{
			vlc.char_table[j] = font_table[j];
		}
		font_table += charscanlines;
		if(ioctl(1, VGALOADCHAR, &vlc) == -1)
		{
			perror("loadfont - ioctl VGALOADCHAR failed, error");
			exit(1);
		}
	}
}

printvgafontattr(charset)
int charset;
{
	struct vgafontattr vfattr;
	static int sizetab[] = { 25, 28, 35, 40, 43, 50 };
	
	vfattr.character_set = charset;

	if(ioctl(1, VGAGETFONTATTR, &vfattr) == -1)
	{
		perror("loadfont - ioctl VGAGETFONTATTR failed, error");
		exit(1);
	}
	printf(" %d  ",charset);
	if(vfattr.font_loaded)
	{

		printf("Loaded ");
		printf(" %2.2d       ", sizetab[vfattr.screen_size]);
		printf(" %2.2d           ",
		       (((int)vfattr.character_scanlines) & 0x1f) + 1);
		printf(" %3.3d",
		       ((int)vfattr.screen_scanlines+0x101));
	}
	else
	{
		printf("Empty");
	}
	printf("\n");
}

printheader()
{
	printf("\nEGA/VGA Charactersets Status Info:\n\n");
	printf("Set Status Lines CharScanLines ScreenScanLines\n");
	printf("--- ------ ----- ------------- ---------------\n");
}

usage()
{
	fprintf(stderr,"\nloadfont - load font into ega/vga font ram for pcvt video driver\n");
	fprintf(stderr,"usage: loadfont -c<cset> -f<filename> -i\n");
	fprintf(stderr,"       -c <cset> characterset to load (ega 0..3, vga 0..7)\n");
	fprintf(stderr,"       -f <name> filename containing binary font data\n");
	fprintf(stderr,"       -i        print status and types of loaded fonts (default)\n");
	exit(1);
}
