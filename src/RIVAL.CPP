/* RIVAL.C */

//#define windowsearch

//#include "rivalgrf.h"
//#include "rivaldat.h"

#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "rivaldef.h"
#include "rivalchi.h"
#include "rivaldis.h"
#include "rivmouse.h"
#include "rivsernm.h"
#include "rivserkn.h"
#include "rivsergv.h"
#include "rivsersh.h"
#include "rivsave.h"
#include "rivsolve.h"

char centrality[100]=
   { 0,0,0,0,0,0,0,0,0,0,
     0,1,1,1,1,1,1,1,1,0,
     0,1,2,2,3,3,2,2,1,0,
     0,2,2,4,4,4,4,2,2,0,
     0,2,3,4,6,6,4,3,2,0,
     0,2,3,4,6,6,4,3,2,0,
     0,2,2,4,4,4,4,2,2,0,
     0,1,2,2,3,3,2,2,1,0,
     0,1,1,1,1,1,1,1,1,0};

char  startbrd[100]=
	{'[','[','[','[','[','[','[','[','[','[',
	 '[','R','P','-','-','-','-','p','r','[',
	 '[','N','P','-','-','-','-','p','n','[',
	 '[','B','P','-','-','-','-','p','b','[',
	 '[','Q','P','-','-','-','-','p','q','[',
	 '[','K','P','-','-','-','-','p','k','[',
	 '[','B','P','-','-','-','-','p','b','[',
	 '[','N','P','-','-','-','-','p','n','[',
	 '[','R','P','-','-','-','-','p','r','[',
	 '[','[','[','[','[','[','[','[','[','w' };


extern unsigned _stklen=32000;
extern unsigned char moveblank[], charblank[];
//extern unsigned char *screenbuffer;
extern unsigned char tempsprite[111*21+2];
extern signed int mousex, mousey, pressed;


struct gametype game;
//long avcount, avtotal;
int timecount=0;
char quit, game_over;
char FLAGnewstart; // indicates that the timer should start for the next move
mvtype dontmove[40];
struct postype current;
char icon, iconmenu,make_current,draws;
char quiescence_depth, g_depth;
int maxbar;
char mainmover, iteration;
int movepointer=0, maxtime;
long   nodes, blacks, whites;
time_t starttime, newtime, oldtime;
long g_seconds;
struct pathtype g_path;
struct optiontype options, doptions;
char nomore, no_more_openings;
mvtype best_at[32];

void makemv(mvtype mv)
{
  struct postype pos;
  pos=current;
  alter(&pos,mv,&current);
  game.movenum++;
  game.previous_moves[game.movenum]=mv;
  game.lastmove=game.movenum;
  movepointer=game.movenum;
  game.whites[game.movenum]=game.whites[game.movenum-1]+whites;
  game.blacks[game.movenum]=game.blacks[game.movenum-1]+blacks;
  FLAGnewstart=1;
}

void check_time(struct pathtype *path)
{
	  timecount++;
	  if (timecount<50) return;
	  timecount=0;
	  oldtime=newtime;
	  if ((newtime=time(NULL)-starttime)>oldtime)
	  {
		  if (mainmover=='b') blacks+=(newtime-oldtime); else whites+=(newtime-oldtime);
		  if (options.analysis)
		  {
				if (mousex>175 && mousey>120) hide_mouse();
				if (mainmover=='b')
				{
					 shownumber(game.blacks[game.movenum]+blacks, 260, 184);
				} else
				{
					 shownumber(game.whites[game.movenum]+whites, 188, 184);
				}
				if (mousex>175 && mousey>120) show_mouse();
				showpath(195,path);
		  }
		  oldtime=newtime;
		  if (options.playstyle==CHAMPIONSHIP || options.playstyle==FIXEDTIME)
		  {
				nomore=(newtime>maxtime);
				if (options.analysis) show_time_bar((int)newtime, (int)maxtime, (mainmover=='b'));
		  }
	  }
}

mvtype get_computer_move(struct postype brd)
{
  int i,j,oldval;
  time_t seconds;
  int top, bottom, prevscore;
  struct movelist moves;
  char goagain;
  mvtype legalmove, openmove;
  struct pathtype curr,path;
  struct postype newpos;
  int thismove, movesleft;
  char todepth;
  mainmover=brd.mvr;
#ifdef windowsearch
  prevscore=0;
#endif
  if (options.game!=REGULARCHESS || !options.library || no_more_openings || !get_opening(&openmove))
  {
	 //if (options.analysis)
	 show_blue_tiles();
	 if (!options.analysis) analoffmessg();
	 computer_move_displays();
	 show_mouse();
	 moves=get_children(&brd);
	 for (i=0; i<40; i++) dontmove[i].f=0;
	 game.movenum=game.movenum+1;
	 draws=0;
	 for (i=1; i<=moves.amount && draws<39; i++)
	 {
		 legalmove=moves.move[i];
		 alter(&brd,legalmove,&newpos);
		 if (previous_pos(newpos, game, 1))	dontmove[draws++]=legalmove;
	 }
	 // check for moves that may draw a position on next move
	 game.movenum=game.movenum-1;
	 nodes=0;
	 nomore=FALSE;
	 for (i=0; i<=11; i++) curr.move[i].f=0;
	 path.value=0;
	 nomore=FALSE;
	 make_current=TRUE;
	 switch (options.playstyle)
	 {
		case FIXEDLEVEL:todepth=options.maxdepth; break;
		case FIXEDTIME:todepth=16; maxtime=options.maxtime; break;
		case CHAMPIONSHIP:todepth=16; maxtime=(options.champtime*60/options.champmoves);
		     break;

	 }
	 g_depth=1;
	 for (i=0; i<32; i++) best_at[i].f=0;
	 for (iteration=1; iteration<=todepth && !nomore; iteration++)
	 {
	  oldval=path.value;
	  if (iteration<=2) quiescence_depth=0; else
			quiescence_depth=iteration+2;

	  path.move[0].f=0;

#ifdef windowsearch
	  top=prevscore+50;
	  bottom=prevscore-50;
	  do
	  {
	    goagain=0;
#else
	  top=32700;
	  bottom=-32700;
#endif
	    switch(options.game)
	    {
		 case KINGLET:kinglet_minimax(&brd,0,top,bottom,curr,&path,0); break;
		 case GIVEAWAY:giveaway_minimax(&brd,0,top,bottom,curr,&path,0); break;
		 case SHATRANJ:shatranj_minimax(&brd,0,top,bottom,curr,&path,FALSE,0); break;
		 case REGULARCHESS:minimax(&brd,0,top,bottom,curr,&path,FALSE,0);
	    }
	    for (i=0; path.move[i].f!=0 && i<8; i++) best_at[i]=path.move[i];
	    best_at[i].f=0;
	    if (path.value>9900)
	    {
		nomore=TRUE;
		make_current=TRUE;
	    }
#ifdef windowsearch
/*	    if (!(path.value>bottom && path.value<top))
	    {
	      top=32700;
	      bottom=-32700;
	      goagain=1;
	    } */
	    if (path.value<bottom)
	    {
	      bottom=-32700;
	      top=path.value;
	      goagain=1;
	    }
	    if (path.value>top)
	    {
	      top=32700;
	      bottom=path.value;
	      goagain=1;
	    }
	  } while (goagain);
	  prevscore=path.value;
#endif
	 }
  } else
  {
	 path.move[0]=openmove;
	 alter(&current, openmove, &newpos);
	 if (mainmover=='b')
		path.move[0].check=check(&newpos, newpos.wking[0]); else
		path.move[0].check=check(&newpos, newpos.bking[0]);
	 path.move[0].lastwin=current.brd[openmove.t];
	 make_current=TRUE;
  }
  if (path.move[0].f==0) make_current=FALSE; // if user requests to make current move then ensure that there is one!
  if (path.value<-10000)
  {
	  path.value=oldval;
  }
  if (nomore && !make_current)
  {
	 path.move[0].t=0;
  } else
  {
	 seconds=time(NULL)-starttime;
	 seconds+=seconds==0;
	 g_path=path;
	 g_seconds=seconds;
  }
  hide_mouse();
  if (options.analysis) display_score_slab(nodes,path.value);
  return(path.move[0]);
}

void menu_option(unsigned char number)
{
  FILE *savefile;
  FILE *optionfile;
  char filename[12], savepos;
  char oldinv; //holds options.inverted when entering setup
  int move_count;
  struct postype pos, newpos;

  switch (number)
  {
	case 100: //avcount=avtotal/avcount;
				 if (g_path.move[0].f>0)
					showstats(nodes,g_seconds,g_depth,g_path); break;
	case 101: rival_help(70); break;
	case 119: rival_help(19); break;
	case 120: options.chessset++; if (options.chessset==3) options.chessset=0; break;
	case 109: options.whiteplayer=USER;
				 options.blackplayer=USER;
				 if (game.movenum>1)
				 {
					 game.movenum=game.movenum-1;
					 pos=game.firstpos;
					 for (move_count=1; move_count<=game.movenum; move_count++)
					 {
						  alter(&pos,game.previous_moves[move_count],&newpos);
						  pos=newpos;
					 }
					 current=newpos;
				 } else
				 {
					 game.movenum=0;
					 current=game.firstpos;
				 }
				 movepointer=game.movenum;
				 no_more_openings=FALSE;
				 break;
	case 110: if (game.lastmove==0)
				 {
					 current=game.firstpos;
				 } else
				 {
					 pos=game.firstpos;
					 for (move_count=1; move_count<=game.lastmove; move_count++)
					 {
						 alter(&pos, game.previous_moves[move_count], &newpos);
						 pos=newpos;
					 }
					 current=newpos;
				 }
				 game.movenum=game.lastmove;
				 movepointer=game.movenum;
				 break;
	case 111: current=game.firstpos; game.movenum=0;
				 movepointer=game.movenum;
				 no_more_openings=FALSE;
				 options.whiteplayer=USER;
				 options.blackplayer=USER;
				 break;
	case 112: if ((savepos=get_savepos('w'))!=0)
				 {
					 strcpy(filename,"RIVAL\0");
					 if (savepos<10)
					 {
						 filename[5]=savepos+48;
						 filename[6]='\0';
					 } else
					 {
						 filename[5]=savepos/10+48;
						 filename[6]=savepos%10+48;
						 filename[7]='\0';
					 }
					 strcat(filename,".SAV");
					 if (confirmation("SAVE GAME"))
					 {
						 savefile=fopen(filename,"w");
						 if (savefile!=NULL)
						 {
							  savefiledata(savefile);
						 } else // if savefile!=NULL
						 {
							  printf("ERROR! SAVE FAILED");
						 }
						 fclose(savefile);
					 } // if confirmation
				 }
				 break;
	case 113: if ((savepos=get_savepos('r'))!=0)
		  {
		     strcpy(filename,"RIVAL\0");
		     if (savepos<10)
		     {
			filename[5]=savepos+48;
			filename[6]='\0';
		     } else
		     {
			filename[5]=savepos/10+48;
			filename[6]=savepos%10+48;
			filename[7]='\0';
		     }
		     strcat(filename, ".SAV");
		     if (((savefile=fopen(filename,"r"))!=NULL) && (confirmation("LOAD GAME")))
		     {
			readfiledata(savefile);
			if (game.movenum==0)
			{
			   current=game.firstpos;
			   movepointer=0;
			} else
			{
			   pos=game.firstpos;
			   for (move_count=1; move_count<=game.movenum; move_count++)
			   {
			     alter(&pos, game.previous_moves[move_count], &newpos);
			     pos=newpos;
			   }
			   current=newpos;
			}
			FLAGnewstart=1;
			movepointer=game.movenum;
		     } //movepointer=game.movenum;
		     fclose(savefile);
		  }
		  break;
	case 107: variant_select(); break;
	case 106: time_select(); break;
	case 127: options.deep_thought=!options.deep_thought; break;
	case 133: break;
	case 118: options.library=!options.library; break;
	case 108: if (game.movenum<game.lastmove)
				 {
					 game.movenum=game.movenum+1;
					 pos=current;
					 alter(&pos,game.previous_moves[game.movenum],&current);
				 }
				 movepointer=game.movenum;
				 break;
	case 103: oldinv=options.inverted;
		  options.inverted=0;
		  enter_setup();
		  options.inverted=oldinv;
		  break;
	case 117: options.analysis=!options.analysis; break;
	case 102: options.inverted=!options.inverted; break;
	case 104: options.whiteplayer=!options.whiteplayer;
				 if (options.whiteplayer==PROGRAM)
					  if (current.mvr=='w')
						  FLAGnewstart=1;
				 break;
	case 105: options.blackplayer=!options.blackplayer;
				 if (options.blackplayer==PROGRAM)
					  if (current.mvr=='b')
						  FLAGnewstart=1;
				 break;
	case 114: if (confirmation("NEW GAME")) initialise(startbrd); no_more_openings=FALSE; break;
	case 115: iconmenu=1; break;
	case 116: iconmenu=0; break;
	case 129: switch (options.sensitivity)
				 {
					 case LOWSENS : options.sensitivity=MEDSENS; break;
					 case MEDSENS : options.sensitivity=HISENS; break;
					 case  HISENS : options.sensitivity=LOWSENS; break;
				 }
				 break;
	case 124: options=doptions; break;
	case 125: optionfile=fopen("options.riv","w");
				 fwrite(&options, sizeof(struct optiontype), 1, optionfile);
				 fclose(optionfile);
				 break;
	case 121: if (options.so<7) options.so+=1; else options.so=0; break;
	case 122: if (options.wo<35) options.wo+=5; else options.wo=0;
				 if (options.wo==options.bo) if (options.wo<35) options.wo+=5; else options.wo=0;
				 break;
	case 123: if (options.bo<35) options.bo+=5; else options.bo=0;
				 if (options.wo==options.bo) if (options.bo<35) options.bo+=5; else options.bo=0;
				 break;
	case 128: solvey(); break;
	case 130: break;
	case 148: options.game=0; break;
	case 126: options.pieceslide=!options.pieceslide; break;
	case 131: if (confirmation("QUIT RIVAL"))
				 {
					 SetTextMode();
					 printf("See you later!");
					 quit=1;
				 }
				 break;
	case 200: if (movepointer>0) movepointer--; break;
	case 201: if (movepointer<game.movenum) movepointer++; break;
	default: break;
  }
}

void set_default_options(void)
{
 doptions.whiteplayer=USER;
 doptions.blackplayer=PROGRAM;
 doptions.maxdepth=3;
 doptions.library=TRUE;
 doptions.analysis=TRUE;
 doptions.inverted=FALSE;
 doptions.pubplay=FALSE;
 doptions.deep_thought=FALSE;
 doptions.wo=5;
 doptions.so=0;
 doptions.bo=0;
 doptions.game=REGULARCHESS;
 doptions.chessset=REGULARSET;
 doptions.playstyle=FIXEDLEVEL;
 doptions.champtime=120;
 doptions.champmoves=40;
 doptions.maxtime=10;
 doptions.pieceslide=TRUE;
 doptions.sensitivity=MEDSENS;
 doptions.messages=1;
}

void read_options(void)
{
 FILE *optionfile;
 optionfile=fopen("options.riv","r");
 if (!optionfile==NULL) fread(&options, sizeof(struct optiontype), 1, optionfile);
 fclose(optionfile);
 options.game=REGULARCHESS; // avoids user confusion
}

//int main(int argc, char *argv[], char *env[])
void main(void)
{
 int i, j;
 mvtype movemade;
 mousex=100;
 mousey=100;
 iconmenu=0;
 set_default_options();
 options=doptions;
 read_options();
 initialise(startbrd);
 initial_displays(current);
 no_more_openings=FALSE;
 quit=game_over=0;
 g_path.move[0].f=0;
 randomize();
 FLAGnewstart=1;
 while(!quit)
 {
   while(game.movenum<maxmoves && !quit)
   {
	 whites=0;
	 blacks=0;
	 if (FLAGnewstart) { starttime=time(NULL); FLAGnewstart=0; }
	 newtime=0;
	 if (!game_over && ((current.mvr=='w' && options.whiteplayer==PROGRAM) || (current.mvr=='b' && options.blackplayer==PROGRAM)))
	      movemade=get_computer_move(current); else
		 movemade=get_player_move(current, game_over);
	 if (kbhit()) { if (getch()==27) { options.whiteplayer=USER; options.blackplayer=USER; } }
	 if (current.mvr=='w') (whites=time(NULL)-starttime); else (blacks=time(NULL)-starttime);
	 if (movemade.t!=0) if (movemade.t<100) makemv(movemade); else {menu_option(movemade.t); game_over=0;}
	 regular_displays(current, movemade);
	 if (!game_over) game_over=over();
	 assert(game.lastmove<maxmoves);
   }
   options.whiteplayer=USER;
   options.blackplayer=USER;
 }
}

