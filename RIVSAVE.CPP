#include <stdio.h>
#include "rivaldef.h"

extern int movepointer;
extern struct gametype game;
extern struct optiontype options;

void readfiledata(FILE *filehandle)
{
	char a,b;
	int i, j;
	options.game=fgetc(filehandle)-65;
	a=fgetc(filehandle)-65;	b=fgetc(filehandle)-65;	game.movenum=b*256+a;
	a=fgetc(filehandle)-65;	b=fgetc(filehandle)-65;	game.lastmove=b*256+a;
	fgetc(filehandle);
	for (i=0; i<10; i++)
	{
	  for (j=0; j<10; j++)
		  game.firstpos.brd[i*10+j]=fgetc(filehandle);
	  fgetc(filehandle);
	}
	game.firstpos.mvr=fgetc(filehandle);
//	game.firstpos.whiteking=fgetc(filehandle)-65;
//	game.firstpos.blackking=fgetc(filehandle)-65;
	game.firstpos.en_pawn=fgetc(filehandle)-65;
	game.firstpos.bmat=fgetc(filehandle)-65;
	game.firstpos.wmat=fgetc(filehandle)-65;
	a=fgetc(filehandle)-65; game.firstpos.total_wmat=(fgetc(filehandle)-65)*256+a;
	a=fgetc(filehandle)-65; game.firstpos.total_bmat=(fgetc(filehandle)-65)*256+a;
	game.firstpos.wrook1_moved=fgetc(filehandle)-65;
	game.firstpos.wrook2_moved=fgetc(filehandle)-65;
	game.firstpos.wking_moved=fgetc(filehandle)-65;
	game.firstpos.brook1_moved=fgetc(filehandle)-65;
	game.firstpos.brook2_moved=fgetc(filehandle)-65;
	game.firstpos.bking_moved=fgetc(filehandle)-65;
	game.firstpos.white_castled=fgetc(filehandle)-65;
	game.firstpos.black_castled=fgetc(filehandle)-65;

	fgetc(filehandle);

	game.firstpos.wrookcount=fgetc(filehandle)-65;
	game.firstpos.wkingcount=fgetc(filehandle)-65;
	game.firstpos.wbishcount=fgetc(filehandle)-65;
	game.firstpos.wqueencount=fgetc(filehandle)-65;
	game.firstpos.wpawncount=fgetc(filehandle)-65;
	game.firstpos.wknightcount=fgetc(filehandle)-65;

	game.firstpos.brookcount=fgetc(filehandle)-65;
	game.firstpos.bkingcount=fgetc(filehandle)-65;
	game.firstpos.bbishcount=fgetc(filehandle)-65;
	game.firstpos.bqueencount=fgetc(filehandle)-65;
	game.firstpos.bpawncount=fgetc(filehandle)-65;
	game.firstpos.bknightcount=fgetc(filehandle)-65;

   fgetc(filehandle);

	for (i=0; i<8; i++) game.firstpos.wrook[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.brook[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.wking[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.bking[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.wbish[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.bbish[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.wpawn[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.bpawn[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.wqueen[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.bqueen[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.wknight[i]=fgetc(filehandle)-65;
	for (i=0; i<8; i++) game.firstpos.bknight[i]=fgetc(filehandle)-65;

	fgetc(filehandle);

	for (i=1; i<maxmoves; i++)
	{
		a=fgetc(filehandle)-64;
		b=fgetc(filehandle)-48;
		game.previous_moves[i].f=a*10+b;
		game.previous_moves[i].lastwin=fgetc(filehandle);
		a=fgetc(filehandle)-64;
		b=fgetc(filehandle)-48;
		game.previous_moves[i].t=a*10+b;

		fgetc(filehandle);

		game.previous_moves[i].check=fgetc(filehandle)-65;

		fgetc(filehandle);

/*		a=fgetc(filehandle);
		b=fgetc(filehandle);
		c=fgetc(filehandle);
		d=fgetc(filehandle);
		game.whites[i]=a*4096+b*256+c*16+d;

		a=fgetc(filehandle);
		b=fgetc(filehandle);
		c=fgetc(filehandle);
		d=fgetc(filehandle);
		game.blacks[i]=a*4096+b*256+c*16+d; */

		fgetc(filehandle);

	}
	movepointer=game.movenum;
}

void savefiledata(FILE *filehandle)
{
	int i, j;
	fputc(options.game+65, filehandle);
	fputc((game.movenum%256)+65, filehandle);
	fputc((game.movenum/256)+65, filehandle);
	fputc((game.lastmove%256)+65, filehandle);
	fputc((game.lastmove/256)+65, filehandle);
	fputc('\n', filehandle);

	for (i=0; i<10; i++)
	{
	  for (j=0; j<10; j++)
		  fputc(game.firstpos.brd[i*10+j], filehandle);
	  fputc('\n', filehandle);
	}
	fputc(game.firstpos.mvr, filehandle);
//	fputc(game.firstpos.whiteking+65, filehandle);
//	fputc(game.firstpos.blackking+65, filehandle);
	fputc(game.firstpos.en_pawn+65, filehandle);
	fputc(game.firstpos.bmat+65, filehandle);
	fputc(game.firstpos.wmat+65, filehandle);
	fputc((game.firstpos.total_wmat%256)+65, filehandle);
	fputc((game.firstpos.total_wmat/256)+65, filehandle);
	fputc((game.firstpos.total_bmat%256)+65, filehandle);
	fputc((game.firstpos.total_bmat/256)+65, filehandle);
	fputc(game.firstpos.wrook1_moved+65, filehandle);
	fputc(game.firstpos.wrook2_moved+65, filehandle);
	fputc(game.firstpos.wking_moved+65, filehandle);
	fputc(game.firstpos.brook1_moved+65, filehandle);
	fputc(game.firstpos.brook2_moved+65, filehandle);
	fputc(game.firstpos.bking_moved+65, filehandle);
	fputc(game.firstpos.white_castled+65, filehandle);
	fputc(game.firstpos.black_castled+65, filehandle);

	fputc('\n', filehandle);

	fputc(game.firstpos.wrookcount+65, filehandle);
	fputc(game.firstpos.wkingcount+65, filehandle);
	fputc(game.firstpos.wbishcount+65, filehandle);
	fputc(game.firstpos.wqueencount+65, filehandle);
	fputc(game.firstpos.wpawncount+65, filehandle);
	fputc(game.firstpos.wknightcount+65, filehandle);

	fputc(game.firstpos.brookcount+65, filehandle);
	fputc(game.firstpos.bkingcount+65, filehandle);
	fputc(game.firstpos.bbishcount+65, filehandle);
	fputc(game.firstpos.bqueencount+65, filehandle);
	fputc(game.firstpos.bpawncount+65, filehandle);
	fputc(game.firstpos.bknightcount+65, filehandle);

	fputc('\n', filehandle);

	for (i=0; i<8; i++) fputc(game.firstpos.wrook[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.brook[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.wking[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.bking[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.wbish[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.bbish[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.wpawn[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.bpawn[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.wqueen[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.bqueen[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.wknight[i]+65, filehandle);
	for (i=0; i<8; i++) fputc(game.firstpos.bknight[i]+65, filehandle);

	fputc('\n', filehandle);
	for (i=1; i<maxmoves; i++)
	{
		fputc((game.previous_moves[i].f/10)+64, filehandle);
		fputc((game.previous_moves[i].f%10)+48, filehandle);
		fputc(game.previous_moves[i].lastwin, filehandle);
		fputc((game.previous_moves[i].t/10)+64, filehandle);
		fputc((game.previous_moves[i].t%10)+48, filehandle);

		fputc('|', filehandle);

		fputc(game.previous_moves[i].check+65, filehandle);

		fputc('|', filehandle);

/*		fputc(game.whites[i]/4096, filehandle);
		fputc(game.whites[i]%4096/256, filehandle);
		fputc(game.whites[i]%256/16, filehandle);
		fputc(game.whites[i]%16, filehandle);

		fputc(game.blacks[i]/4096, filehandle);
		fputc(game.blacks[i]%4096/256, filehandle);
		fputc(game.blacks[i]%256/16, filehandle);
		fputc(game.blacks[i]%16, filehandle); */

		fputc('\n', filehandle);
	}

}
