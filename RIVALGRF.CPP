//*************************************************************************//
//* Rusky presents LOW level graphics routinesfor your pleasure. Feb '94. *//
//*************************************************************************//

#include <dos.h>
#include <mem.h>
#include <string.h>
#include "rivalgrf.h"


unsigned char letters[1548]=
{
00,11,12,11,11,00,
11,00,00,00,12,11,
11,00,00,11,00,11,
11,00,11,00,00,11,
11,12,00,00,00,11,
00,11,11,12,11,00,

00,00,00,12,00,00,
00,00,12,11,00,00,
00,00,00,11,00,00,
00,00,00,11,00,00,
00,00,00,11,00,00,
00,00,12,11,12,00,

00,11,11,11,11,00,
12,00,00,00,00,11,
00,00,00,00,00,11,
00,12,11,11,11,00,
11,00,00,00,00,00,
11,11,11,11,11,12,

12,11,11,11,11,11,
00,00,00,00,00,11,
00,00,00,00,12,00,
00,00,00,00,00,11,
12,00,00,00,00,11,
00,11,11,11,11,00,

12,00,00,00,00,00,
11,00,00,00,00,00,
11,00,00,11,00,00,
12,11,11,12,11,12,
00,00,00,11,00,00,
00,00,00,11,00,00,

11,11,11,11,11,12,
11,00,00,00,00,00,
12,11,11,11,11,00,
00,00,00,00,00,11,
12,00,00,00,00,11,
00,11,11,11,11,00,

00,11,11,11,12,00,
11,00,00,00,00,00,
12,11,11,11,11,00,
11,00,00,00,00,11,
11,00,00,00,00,11,
00,11,11,11,12,00,

12,11,11,11,11,11,
00,00,00,00,11,00,
00,00,00,11,00,00,
00,00,11,00,00,00,
00,11,00,00,00,00,
12,00,00,00,00,00,

00,11,11,11,12,00,
11,00,00,00,00,11,
00,12,11,11,12,00,
11,00,00,00,00,11,
11,00,00,00,00,11,
00,12,11,11,11,00,

00,12,11,11,11,12,
11,00,00,00,00,11,
11,00,00,00,00,11,
00,11,11,11,11,12,
00,00,00,00,00,11,
00,00,00,00,00,12,

00,00,00,00,00,00,   //:
00,00,12,11,00,00,
00,00,11,11,00,00,
00,00,00,00,00,00,
00,00,12,11,00,00,
00,00,11,11,00,00,

15,15,15,15,15,15,  //;
15,15,15,15,15,15,
15,15,15,15,15,15,
15,15,15,15,15,15,
15,15,15,15,15,15,
15,15,15,15,15,15,

12,11,11,11,11,12,  // <
11,11,11,11,11,11,
11,11,11,11,11,11,
11,11,11,11,11,11,
11,11,11,11,11,11,
12,11,11,11,11,12,

00,00,00,00,00,00,   // = is a full stop.
00,00,00,00,00,00,
00,00,00,00,00,00,
00,00,00,00,00,00,
12,11,00,00,00,00,
11,11,00,00,00,00,

00,00,00,00,00,00,   // > is a comma.
00,00,00,00,00,00,
00,00,00,00,00,00,
12,11,00,00,00,00,
11,11,00,00,00,00,
00,12,00,00,00,00,

00,00,12,11,00,00,   // ? is exclamation
00,00,12,11,00,00,
00,00,11,11,00,00,
00,00,11,11,00,00,
00,00,00,00,00,00,
00,00,12,11,00,00,

00,00,00,00,00,00,
00,00,00,00,00,12,
00,00,00,00,11,00,
00,00,00,11,00,00,
12,00,11,00,00,00,
00,11,00,00,00,00,

00,00,12,12,00,00,
00,00,11,11,00,00,
00,11,00,00,11,00,
00,12,11,11,12,00,
11,00,00,00,00,11,
12,00,00,00,00,12,

12,11,11,11,12,00,
11,00,00,00,00,11,
12,11,11,11,12,00,
11,00,00,00,00,11,
11,00,00,00,00,11,
12,11,11,11,12,00,

00,12,11,11,12,00,
11,00,00,00,00,11,
11,00,00,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,11,
00,12,11,11,12,00,

12,11,11,12,00,00,
11,00,00,00,11,00,
11,00,00,00,00,11,
11,00,00,00,00,11,
11,00,00,00,11,00,
12,11,11,12,00,00,

12,11,11,11,12,00,
11,00,00,00,00,00,
12,11,11,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,00,
12,11,11,11,12,00,

12,11,11,11,12,00,
11,00,00,00,00,00,
12,11,11,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,00,
12,00,00,00,00,00,

00,11,11,11,11,00,
12,00,00,00,00,12,
11,00,00,00,00,00,
11,00,00,00,11,12,
11,00,00,00,00,11,
00,12,11,11,11,12,

12,00,00,00,00,12,
11,00,00,00,00,11,
12,11,11,11,11,12,
11,00,00,00,00,11,
11,00,00,00,00,11,
12,00,00,00,00,12,

00,11,12,11,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,11,12,11,00,00,

00,00,00,00,00,12,
00,00,00,00,00,11,
00,00,00,00,00,11,
12,00,00,00,00,11,
11,00,00,00,00,11,
00,11,11,11,11,00,

12,00,00,00,12,00,
11,00,00,11,00,00,
11,00,12,00,00,00,
11,11,00,11,00,00,
11,00,00,00,11,00,
12,00,00,00,00,12,

12,00,00,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,00,
11,00,00,00,00,00,
12,11,11,11,11,12,

12,00,00,00,00,12,
11,11,00,00,11,11,
11,00,12,12,00,11,
11,00,00,00,00,11,
11,00,00,00,00,11,
12,00,00,00,00,12,

12,11,00,00,00,12,
11,00,11,00,00,11,
11,00,00,11,00,11,
11,00,00,11,00,11,
11,00,00,00,11,11,
12,00,00,00,00,12,

00,11,11,11,12,00,
12,00,00,00,00,11,
11,00,00,00,00,11,
11,00,00,00,00,11,
11,00,00,00,00,12,
00,12,11,11,11,00,

12,11,11,11,11,00,
11,00,00,00,00,12,
11,00,00,00,00,11,
11,11,11,11,11,00,
11,00,00,00,00,00,
12,00,00,00,00,00,

00,12,11,11,11,00,
11,00,00,00,00,12,
11,00,00,00,00,11,
11,00,00,12,00,11,
12,00,00,00,12,11,
00,11,11,11,11,00,

12,11,11,11,11,00,
11,00,00,00,00,11,
11,00,00,00,00,11,
12,11,11,11,11,00,
11,00,00,00,00,11,
12,00,00,00,00,12,

00,11,11,11,12,00,
11,00,00,00,00,00,
00,11,11,11,11,00,
00,00,00,00,00,11,
12,00,00,00,00,11,
00,11,11,11,11,00,

12,11,11,11,12,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,12,00,00,00,

12,00,00,00,00,12,
11,00,00,00,00,11,
11,00,00,00,00,11,
11,00,00,00,00,11,
11,00,00,00,00,11,
00,12,11,11,12,00,

12,00,00,00,00,12,
11,00,00,00,00,11,
00,11,00,00,11,00,
00,11,00,00,11,00,
00,00,11,11,00,00,
00,00,12,12,00,00,

12,00,00,00,00,12,
11,00,00,00,00,11,
11,00,00,00,00,11,
11,00,12,12,00,11,
11,11,00,00,11,11,
12,00,00,00,00,12,

12,00,00,00,00,12,
00,11,00,00,11,00,
00,00,12,11,00,00,
00,00,11,11,00,00,
00,11,00,00,11,00,
12,00,00,00,00,12,

12,00,00,00,12,00,
00,11,00,11,00,00,
00,00,12,00,00,00,
00,00,11,00,00,00,
00,00,11,00,00,00,
00,00,12,00,00,00,

12,11,11,11,11,12,
00,00,00,00,11,00,
00,00,00,11,00,00,
00,00,11,00,00,00,
00,11,00,00,00,00,
12,11,11,11,11,12
};

void pixelvid(int x,int y,int colour,unsigned char  far *memstart)
{
	unsigned char far *pixpntr;  	/* Pointer for direct video memory access */
	pixpntr = memstart +(y*320) + x;
	pixpntr[0] = colour;
}

void linevert(int x1,int y1,int y2, int colour,unsigned char  far *memstart)
{
	int  y;
	y2++;
	for (y=y1;y != y2;y++)
		pixelvid(x1,y,colour,memstart);
}

void linehori(int x1,int x2,int y1, int colour,unsigned char  far *memstart)
{
	int x;
	x2++;
	for (x=x1;x != x2;x++)
		pixelvid(x,y1,colour,memstart);
}

void drawsquare(int x1,int y1,int x2,int y2,char col,unsigned char  far *memstart)
{
	linehori(x1,x2,y1,col,memstart);
	linehori(x1,x2,y2,col,memstart);
	linevert(x1,y1,y2,col,memstart);
	linevert(x2,y1,y2,col,memstart);
}

void sprxy(int x,int y,unsigned char far *sprpntr,char offset,unsigned char  far *memstart)
// Sprite display routine. All '0' will be clear. Use 16 to mask.
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	unsigned char limx = sprpntr[0];
	unsigned char limy = sprpntr[1] -1;
	unsigned char loopy,loopx;
	unsigned char memlimy=y+limy;
	unsigned int counter=2;
	for (loopy=y; loopy<=memlimy; loopy++)
	{
	  vidpntr = memstart+(loopy*320) + x;
	  for (loopx=0; loopx<limx; loopx++)
			{
			  if (sprpntr[counter] != 0)
			  {
			  if (sprpntr[counter]==16 || sprpntr[counter]<96 || sprpntr[counter]>102)
				vidpntr[loopx] = sprpntr[counter]; else
				vidpntr[loopx] = sprpntr[counter]+offset;
			  }
			  counter++;
			}
	}
}

void super_sprxy(int x,int y,unsigned char far *sprpntr,unsigned char  far *memstart)
// Sprite display routine. All '0' will be clear. Use 16 to mask.
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	unsigned char limx = sprpntr[0];
	unsigned char limy = sprpntr[1] -1;
	unsigned char loopy;
	unsigned char memlimy=y+limy;
	for (loopy=y; loopy<=memlimy; loopy++)
	{
	  vidpntr = memstart+(loopy*320) + x;
	  _fmemcpy(vidpntr, sprpntr+((loopy-y)*limx)+2, limx);
	}
}

void sqrxy(int x,int y,int sizex, int sizey, unsigned char colournum,unsigned char  far *memstart)
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	unsigned char limx = sizex;
	unsigned char limy = sizey -1;
	unsigned char loopy,loopx;
	for (loopy=y; loopy<=y+limy; loopy++)
	  {
		vidpntr = memstart+(loopy*320) + x;
		for (loopx=0; loopx<limx; loopx++) vidpntr[loopx] = colournum;
	  }
}

void shadesqrxy(int x,int y,int sizex, int sizey, unsigned char colournum, unsigned char light, unsigned char dark, unsigned char  far *memstart)
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	unsigned char limx = sizex;
	unsigned char limy = sizey -1;
	unsigned char loopy,loopx;
	for (loopy=y; loopy<=y+limy; loopy++)
	  {
		vidpntr = memstart+(loopy*320) + x;
		for (loopx=0; loopx<limx; loopx++) vidpntr[loopx] = colournum;
	  }
	linehori(x,x+sizex,y,light,memstart);
	linevert(x+sizex,y,y+sizey,dark,memstart);
	linevert(x,y,y+sizey,light,memstart);
	linehori(x,x+sizex,y+sizey,dark,memstart);
}


void g_SetVGA(void)
{
	union REGS regs;
	regs.h.al = 0x13;                    /* 256-colour VGA */
	regs.h.ah = 0x00;                    /* Set graphics mode */
	int86(0x10, &regs, &regs);           /* DOS interrupt 10h */
}

void g_SetTxt(void)
{
	union REGS regs;
	regs.h.al = 0x03;                    /* 16-colour VGA text mode */
	regs.h.ah = 0x00;                    /* Set graphics mode */
	int86(0x10, &regs, &regs);           /* DOS interrupt 10h */
}

void windowtovid(int x1, int y1, int x2, int y2, unsigned char far *buffpntr)
{
	unsigned int register loopy;
	unsigned int ind;
	unsigned char *vidpntr=(unsigned char *)vidmemstart;
	for (loopy=y1; loopy<=y2; loopy++)
	{
		ind=loopy*320+x1;
//		for (loopx=0; loopx<(x2-x1); loopx++)
//			vidpntr[ind+loopx]=buffpntr[loopx+ind];
		_fmemcpy(vidpntr+ind,buffpntr+ind,(x2-x1));
	}
}

void fadegraphbuff(int x1, int y1, int x2, int y2,char less,char minimum, unsigned char far *buffpntr)
{
	unsigned char loopy;
	unsigned int loopx;
	unsigned int ind;
	unsigned char *vidpntr;
	for (loopy=y1; loopy<=y2; loopy++)
	{
		ind=loopy*320+x1;
		vidpntr=(unsigned char *)buffpntr+ind;
		for (loopx=0; loopx<(x2-x1); loopx++)
			if (buffpntr[loopx+ind]-less >= minimum)
				vidpntr[loopx]=buffpntr[loopx+ind]-less;
				else
				vidpntr[loopx]=minimum;
	}
}

void brightgraphbuff(int x1, int y1, int x2, int y2,char plus,char maximum, unsigned char far *buffpntr)
{
	unsigned char loopy;
	unsigned int loopx;
	unsigned int ind;
	unsigned char far *vidpntr;
	for (loopy=y1; loopy<=y2; loopy++)
	{
		ind=loopy*320+x1;
		vidpntr=(unsigned char *)buffpntr+ind;
		for (loopx=0; loopx<=(x2-x1); loopx++)
			if (buffpntr[loopx+ind]+plus <= maximum)
				vidpntr[loopx]=buffpntr[loopx+ind]+plus;
				else
				vidpntr[loopx]=maximum;
	}
}

void setvgapalette(unsigned char far *p)
{
		union REGS r;
		struct SREGS sr;
		r.x.ax=0x1012;
		r.x.bx =0;
		r.x.cx=256;
		r.x.dx=FP_OFF(p);
		sr.es=FP_SEG(p);
		int86x(0x10,&r,&r,&sr);
}

void makesprite(int x1, int y1, int x2, int y2, unsigned char far *spritename, unsigned char  *buffpntr)
{
  int x, y, counter;
  spritename[0]=(x2-x1)+1;
  spritename[1]=(y2-y1)+1;
  counter=2;
  for (y=y1; y<=y2; y++)
	for (x=x1; x<=x2; x++)
	{
	  spritename[counter]=buffpntr[(y*320)+x];
	  counter++;
	}
}

void enlargexy(int x,int y,unsigned char  far *sprpntr,char offset,unsigned char  far *memstart)
// Sprite display routine. All '0' will be clear. Use 16 to mask.
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	char bigger=2;
	int c, b;
	unsigned char limx = sprpntr[0];
	unsigned char limy = sprpntr[1] -1;
	unsigned char loopy,loopx;
	unsigned char memlimy=y+(limy*bigger);
	unsigned int counter=2;
	for (loopy=y; loopy<=memlimy; loopy+=bigger)
	  {
	  vidpntr = memstart+(loopy*320) + x;
	  for (loopx=0; loopx<=(limx*bigger)-bigger; loopx+=bigger)
			{
			if (sprpntr[counter] != 0)
			{
			  if (sprpntr[counter]==16 || sprpntr[counter]<96 || sprpntr[counter]>102)
			  for (b=0; b<bigger; b++)
				 for (c=loopx+320*b; c<(loopx+320*b)+bigger; c++) vidpntr[c]=sprpntr[counter]; else
			  for (b=0; b<bigger; b++)
				 for (c=loopx+320*b; c<(loopx+320*b)+bigger; c++) vidpntr[c]=sprpntr[counter]+offset;
			}
			counter++;
			}
	  }
}

void letxy(int x, int y, char letter, signed char offset, unsigned char  far *memstart, unsigned char backg)
// Displays a letter.  Offset is added to the palette number to be used.
// If Offset is sub-zero, then the background will be see-through.
{
	unsigned char far *vidpntr;  	/* Pointer for direct video memory access */
	unsigned char *sprpntr;
	unsigned char background;
	unsigned counter=0;
	unsigned char limx = 6;
	unsigned char limy = 5;
	unsigned char loopy,loopx;
	if (offset<0)
	{
	  offset=-offset;
	  background=0;
	} else
	background=backg;

	sprpntr = letters+((letter-48)*36);
	for (loopy=y; loopy<=y+limy; loopy++)
	{
	  vidpntr = memstart+(loopy*320) + x;
	  for (loopx=0; loopx<limx; loopx++)
	  {
		if (sprpntr[counter] != 0)
		{
				vidpntr[loopx] = sprpntr[counter]+offset;
		} else
		{
		  if (background) vidpntr[loopx]=background;
		}
		counter++;
	  }
	}

}

void stringxy(int x, int y, char *st, signed char offset, unsigned char far *memstart, unsigned char backg)
{
  char strcount, length;
  length=strlen(st);
  for (strcount=0; strcount<length; strcount++)
  {
	if (st[strcount]!=' ')
	  letxy(x+(strcount*8), y, st[strcount], offset, memstart, backg); else
	  sqrxy(x+(strcount*8), y, 8, 7, backg);
  }
}