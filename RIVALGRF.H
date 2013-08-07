#define vidmemstart 0xA0000000L

void pixelvid(int x,int y,int colour,unsigned char far *memstart=(unsigned char *)vidmemstart);
void linevert(int x1,int y1,int y2, int colour,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void linehori(int x1,int x2,int y1, int colour,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void drawsquare(int x1,int y1,int x2,int y2,char col,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void sprxy(int x,int y,unsigned char far *sprpntr,char offset,unsigned char far *memstart=(unsigned char *)vidmemstart);
void super_sprxy(int x,int y,unsigned char far *sprpntr,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void sqrxy(int x,int y,int sizex, int sizey, unsigned char colournum,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void shadesqrxy(int x,int y,int sizex, int sizey, unsigned char colournum, unsigned char light, unsigned char dark, unsigned char  far *memstart=(unsigned char *)vidmemstart);
void g_SetVGA(void);
void g_SetTxt(void);
void windowtovid(int x1, int y1, int x2, int y2, unsigned char far *buffpntr=(unsigned char *)vidmemstart);
void fadegraphbuff(int x1, int y1, int x2, int y2,char less,char minimum, unsigned char far *buffpntr=(unsigned char *)vidmemstart);
void brightgraphbuff(int x1, int y1, int x2, int y2,char plus,char maximum, unsigned char far *buffpntr=(unsigned char *)vidmemstart);
void setvgapalette(unsigned char far *p);
void makesprite(int x1, int y1, int x2, int y2, unsigned char *spritename, unsigned char far *buffpntr=(unsigned char *)vidmemstart);
void enlargexy(int x,int y,unsigned char far *sprpntr,char offset,unsigned char  far *memstart=(unsigned char *)vidmemstart);
void letxy(int x, int y, char letter, signed char offset, unsigned char  far *memstart=(unsigned char *)vidmemstart, unsigned char backg=23);
void stringxy(int x, int y, char *st,  signed char offset, unsigned char  far *memstart=(unsigned char *)vidmemstart, unsigned char backg=23);

