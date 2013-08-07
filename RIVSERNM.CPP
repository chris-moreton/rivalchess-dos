#include <stdlib.h>
#include <stdio.h>
#include "rivaldef.h"
#include "rivalchi.h"
#include "rivmouse.h"
#include "rivaldis.h"

extern char nomore, iteration, quiescence_depth, g_depth, draws, mainmover, make_current, no_more_openings;
extern gametype game;
extern struct postype current;
extern signed int pressed, mousex, mousey;
extern mvtype dontmove[];
extern long nodes;
extern int maxbar;
extern optiontype options;
extern char centrality[];
extern void check_time(struct pathtype *path);

char get_opening(mvtype *move)
{
  struct postype dumpos;
  mvtype reply[1000];
  char legal, hit;
  struct movelist mvs;
  int replies;
  int i;
  unsigned char amount;
  mvtype playmove;
  FILE *openingfile;
  if ((openingfile=fopen("OPENINGS.LIB","r"))!=NULL)
  {
	 replies=0;
	 reply[0].f=0;
	 while ((amount=fgetc(openingfile))!=255)
	 {
		amount-=65;
		hit=TRUE;
		for (i=1; i<=amount; i++)
		{
			playmove.f=fgetc(openingfile)-65;
			playmove.t=fgetc(openingfile)-65;
			if (hit && i<=game.movenum && (playmove.f!=game.previous_moves[i].f || playmove.t!=game.previous_moves[i].t)) hit=FALSE;
			if (i==game.movenum+1 && hit && replies+1<1000) reply[++replies]=playmove;
		}
		fgetc(openingfile); // quality
	 }
  }
  fclose(openingfile);
  if (replies==0)
  {
	  no_more_openings=TRUE;
	  return(FALSE);
  }
  *move=reply[random(replies)+1];
  mvs=get_children(&current);
  legal=FALSE;
  for (i=1; i<=mvs.amount; i++)
  {
	 if ((move->f==mvs.move[i].f && move->t==mvs.move[i].t)) legal=no_check_position(&current,*move,&dumpos);
  }
  if (legal) return(TRUE);
  no_more_openings=TRUE;
  return(FALSE);
}

int evaluate(struct postype *pos)
{
  char sq, i;
  SQUARE squareindex;
  int material=pos->total_wmat-pos->total_bmat;
//  nodes++;
  for (i=0; i<=pos->wpawncount; i++)
  {
			squareindex=pos->wpawn[i];
			if (pos->brd[squareindex-1]=='P' && pos->brd[squareindex+11]=='P') material-=12;
			if (pos->brd[squareindex+1]=='P' && pos->brd[squareindex+11]=='P') material-=10;
			if (pos->brd[squareindex+1]=='P' && pos->brd[squareindex+10]=='P') material-=7;
			if (pos->brd[squareindex+2]=='P' && pos->brd[squareindex+11]=='P') material-=10;
			if (pos->brd[squareindex+11]>'a' && pos->brd[squareindex-9]>'a') material+=25;
			if (pos->wmat<14) material+=((squareindex%10)*abs((pos->bking[0]/10)-squareindex/10));
  }
  for (i=0; i<=pos->bpawncount; i++)
  {
			squareindex=pos->bpawn[i];
			if (pos->brd[squareindex+1]=='p' && pos->brd[squareindex-11]=='p') material+=12;
			if (pos->brd[squareindex-1]=='p' && pos->brd[squareindex-11]=='p') material+=10;
			if (pos->brd[squareindex-1]=='p' && pos->brd[squareindex-10]=='p') material+=7;
			if (pos->brd[squareindex-2]=='p' && pos->brd[squareindex-11]=='p') material+=10;
			if (pos->brd[squareindex-11]>'A' && pos->brd[squareindex-11]<'Z' &&
			    pos->brd[squareindex+9]>'A' && pos->brd[squareindex+9]<'Z') material-=25;
			if (pos->bmat<14)	material-=((9-squareindex%10)*abs((pos->wking[0]/10)-squareindex/10));
  }
  for (i=0; i<=pos->wrookcount; i++)
  {
			squareindex=pos->wrook[i];
			sq=10+(squareindex%10); // start search at left of board
			pos->brd[squareindex]='-';
			if (pos->brd[sq]=='R' || pos->brd[sq+10]=='R' || pos->brd[sq+20]=='R' || pos->brd[sq+30]=='R' ||
								  pos->brd[sq+40]=='R' || pos->brd[sq+50]=='R' || pos->brd[sq+60]=='R' || pos->brd[sq+70]=='R')
									  material+=8;
			sq=(squareindex-(squareindex%10))+1; // start search at bottom of board
			if (pos->brd[sq]=='R' || pos->brd[sq+1]=='R' || pos->brd[sq+2]=='R' || pos->brd[sq+3]=='R' ||
					 pos->brd[sq+4]=='R' || pos->brd[sq+5]=='R' || pos->brd[sq+6]=='R' || pos->brd[sq+7]=='R')
						  material+=8;
			if (pos->brd[sq+1]!='P' && pos->brd[sq+2]!='P' && pos->brd[sq+3]!='P' &&
								  pos->brd[sq+4]!='P' && pos->brd[sq+5]!='P' && pos->brd[sq+6]!='P')
									  material+=8;
			pos->brd[squareindex]='R';
			if (squareindex>70) material+=22;
			if (pos->bmat<14)
			{
				if (pos->bking[0]%10<squareindex%10) material+=((9-squareindex%10)*2);
				if (pos->bking[0]/10<squareindex/10) material+=((9-squareindex/10)*2);
				if (pos->bking[0]%10>squareindex%10) material+=((squareindex%10)*2);
				if (pos->bking[0]/10>squareindex/10) material+=((squareindex/10)*2);
			}
  }
  for (i=0; i<=pos->brookcount; i++)
  {
			squareindex=pos->brook[i];
			sq=10+(squareindex%10); // start search at left of board
			pos->brd[squareindex]='-';
			if (pos->brd[sq]=='r' || pos->brd[sq+10]=='r' || pos->brd[sq+20]=='r' || pos->brd[sq+30]=='r' ||
								  pos->brd[sq+40]=='r' || pos->brd[sq+50]=='r' || pos->brd[sq+60]=='r' || pos->brd[sq+70]=='r')
									  material-=8;
							 sq=(squareindex-(squareindex%10))+1; // start search at bottom of board
			if (pos->brd[sq]=='r' || pos->brd[sq+1]=='r' || pos->brd[sq+2]=='r' || pos->brd[sq+3]=='r' ||
								  pos->brd[sq+4]=='r' || pos->brd[sq+5]=='r' || pos->brd[sq+6]=='r' || pos->brd[sq+7]=='r')
										material-=8;
			if (pos->brd[sq+1]!='p' && pos->brd[sq+2]!='p' && pos->brd[sq+3]!='p' &&
								  pos->brd[sq+4]!='p' && pos->brd[sq+5]!='p' && pos->brd[sq+6]!='p')
									  material-=8;
			pos->brd[squareindex]='r';
			if (squareindex<30) material-=22;
			if (pos->wmat<14)
			{
								  if (pos->wking[0]%10<squareindex%10) material-=((9-squareindex%10)*2);
								  if (pos->wking[0]/10<squareindex/10) material-=((9-squareindex/10)*2);
								  if (pos->wking[0]%10>squareindex%10) material-=((squareindex%10)*2);
								  if (pos->wking[0]/10>squareindex/10) material-=((squareindex/10)*2);
			}
  }
  for (i=0; i<=pos->wknightcount; i++)
  {
			squareindex=pos->wknight[i];
			material+=(centrality[squareindex]);
			if (squareindex<20) material-=9;
  }
  for (i=0; i<=pos->bknightcount; i++)
  {
			squareindex=pos->bknight[i];
			material-=(centrality[squareindex]);
			if (squareindex>80) material+=9;
  }
  for (i=0; i<=pos->wqueencount; i++)
  {
			squareindex=pos->wqueen[i];
			material-=(min(abs(squareindex/10-pos->bking[0]/10),abs(squareindex%10-pos->bking[0]%10)));
			if (pos->bmat<14)
			{
				if (pos->bking[0]%10<squareindex%10) material+=((9-squareindex%10)*2);
				if (pos->bking[0]/10<squareindex/10) material+=((9-squareindex/10)*2);
				if (pos->bking[0]%10>squareindex%10) material+=((squareindex%10)*2);
				if (pos->bking[0]/10>squareindex/10) material+=((squareindex/10)*2);
			}
  }
  for (i=0; i<=pos->bqueencount; i++)
  {
			squareindex=pos->bqueen[i];
			material+=(min(abs(squareindex/10-pos->wking[0]/10),abs(squareindex%10-pos->wking[0]%10)));
			if (pos->wmat<14)
			{
				if (pos->wking[0]%10<squareindex%10) material-=((9-squareindex%10)*2);
				if (pos->wking[0]/10<squareindex/10) material-=((9-squareindex/10)*2);
				if (pos->wking[0]%10>squareindex%10) material-=((squareindex%10)*2);
				if (pos->wking[0]/10>squareindex/10) material-=((squareindex/10)*2);
			}
  }

  for (i=0; i<=pos->wbishcount; i++)
  {
			squareindex=pos->wbish[i];
			for (sq=squareindex; pos->brd[sq=sq-11]!='['; material+=((pos->brd[sq]!='P') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq+11]!='['; material+=((pos->brd[sq]!='P') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq-9]!='['; material+=((pos->brd[sq]!='P') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq+9]!='['; material+=((pos->brd[sq]!='P') ? 2 : 0));
			if (squareindex<20) material-=11;
  }
  for (i=0; i<=pos->bbishcount; i++)
  {
			squareindex=pos->bbish[i];
			for (sq=squareindex; pos->brd[sq=sq-11]!='['; material-=((pos->brd[sq]!='p') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq+11]!='['; material-=((pos->brd[sq]!='p') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq-9]!='['; material-=((pos->brd[sq]!='p') ? 2 : 0));
			for (sq=squareindex; pos->brd[sq=sq+9]!='['; material-=((pos->brd[sq]!='p') ? 2 : 0));
			if (squareindex>80) material+=11;
  }

  if (pos->bmat<14)
  {
	 material+=(centrality[pos->wking[0]]*2);
  } else
  {
	 if (pos->wking[0]==7 || pos->wking[0]==2) material+=10; else
		if (pos->wking[0]==1 || pos->wking[0]==3 || pos->wking[0]==6 || pos->wking[0]==8) material+=7;

  }
  if (pos->wmat<14)
  {
	 material-=(centrality[pos->bking[0]]*2);
  } else
  {
	 if (pos->bking[0]==7 || pos->bking[0]==2) material-=10; else
		if (pos->bking[0]==1 || pos->bking[0]==3 || pos->bking[0]==6 || pos->bking[0]==8) material-=7;
  }

  if (!pos->black_castled && pos->bking_moved) material+=9;
  if (!pos->white_castled && pos->wking_moved) material-=9;
  return (pos->mvr=='w') ? material : -material;
}

void quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path,
	  char lastmovecheck, char extend)
{
  int child;
  char movestart;
  struct movelist mvs;
  struct pathtype bestpath, newpath;
  mvtype legalmove;
  struct postype newpos;
  if (nomore) return;
  if (depth>quiescence_depth+extend)
  {
	  path->move[depth].f=0;
	  current.move[depth].f=0;
	  path->value=evaluate(pos);
	  current.value=path->value;
	  return;
  }
  if (lastmovecheck)
  {
	 mvs=get_children(pos);
	 for (movestart=1; movestart<=mvs.amount; movestart++)
	 {
	  if (no_check_position(pos,(legalmove=mvs.move[movestart]),&newpos))
	  {
		 if (pos->mvr=='w') legalmove.check=check(&newpos,newpos.bking[0]); else legalmove.check=check(&newpos,newpos.wking[0]);
		 break;
	  }
	 }
	 if (movestart<=mvs.amount)
	 {
		 current.move[depth]=legalmove;
		 quiesce_evaluate(&newpos,depth+1,-calcbound,-usebound,current,&newpath,legalmove.check, extend);
		 newpath.value=-newpath.value;
		 if (newpath.value>calcbound && !nomore)
		 {
			 calcbound=newpath.value;
			 bestpath=newpath;
			 bestpath.move[depth]=legalmove;
			 if (depth==0)
			{
				if (options.analysis) showpath(260,&bestpath);
				g_depth=iteration;
				nomore=(newpath.value>9000);
			}
		 }
	} else //  movestart<=mvs.amount
	{
		 path->move[depth].f=0;
		 path->value=-10000+depth;
		 return;
	 }
  } else // lastmovecheck
  {
		if ((calcbound=evaluate(pos))>=usebound)
		{
			path->value=calcbound;
			return;
		 }
		 bestpath.move[depth].f=0; // null move
		 mvs=q_get_children(pos);
		 movestart=0;
  }
  for (child=movestart+1; child<=mvs.amount; child++)
  {
	  nodes++;
	  if (calcbound>=usebound)
	  {
		 *path=bestpath;
		 path->value=calcbound;
		 check_time(&current);
		 return;
	  }
	  if (!nomore && no_check_position(pos,(legalmove=mvs.move[child]),&newpos))
	  {
		 if (pos->mvr=='w') legalmove.check=check(&newpos,newpos.bking[0]); else legalmove.check=check(&newpos,newpos.wking[0]);
		 current.move[depth]=legalmove;
		 quiesce_evaluate(&newpos,depth+1,-calcbound,-usebound,current,&newpath,legalmove.check,extend);
		 newpath.value=-newpath.value;
		 if (newpath.value>calcbound)
		 {
			 calcbound=newpath.value;
			 bestpath=newpath;
			 bestpath.move[depth]=legalmove;
			 if (depth==0)
			 {
				 if (options.analysis) showpath(260,&bestpath);
				 g_depth=iteration;
				 nomore=(newpath.value>9000);
			 }
		 }
	  } // !nomore
  } // for child
*path=bestpath;
path->value=calcbound;
} // function quiesce_evaluate

void minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char lastmovecheck,
	  char extend)
{
 int child;
 char loop, movestart;
 struct movelist mvs;
 struct pathtype bestpath, newpath;
 mvtype legalmove;
 struct postype newpos;
 if (nomore) return;
 if (depth>=iteration+extend)
 {
	path->move[depth].f=current.move[depth].f=0;
	quiesce_evaluate(pos, depth, usebound, calcbound, current, &newpath, lastmovecheck,extend);
	path->value=current.value=newpath.value;
	return;
 }
	mvs=get_children(pos);
   if (lastmovecheck && extend<2 && iteration>=3) extend++;
	for (movestart=1; movestart<=mvs.amount; movestart++)
	{
	  if (no_check_position(pos,(legalmove=mvs.move[movestart]),&newpos))
	  {
		 if (pos->mvr=='w') legalmove.check=check(&newpos,newpos.bking[0]); else legalmove.check=check(&newpos,newpos.wking[0]);
		 break;
	  }
	}
	if (movestart<=mvs.amount)
	{
	  if (depth==0)
	  {
		 for (loop=0; loop<draws; loop++)
		 if (dontmove[loop].f==legalmove.f && dontmove[loop].f==legalmove.f && dontmove[loop].t==legalmove.t && dontmove[loop].t==legalmove.t)
		 {
			  newpath.value=0;
			  path->move[1].f=0;
			  newpath.move[1].f=0;
			  current.move[0]=legalmove;
			  goto drawjumpother;
		 }
	  }
	  current.move[depth]=legalmove;
	  minimax(&newpos,depth+1,-calcbound,-usebound,current,&newpath,legalmove.check,extend);
	  newpath.value=-newpath.value;
drawjumpother:;
	  if (newpath.value>calcbound && !nomore)
	  {
		  calcbound=newpath.value;
		  bestpath=newpath;
		  bestpath.move[depth]=legalmove;
		  if (depth==0)
		  {
			  if (options.analysis)
			  {
				  showpath(260,&bestpath);
				  show_iteration(iteration);
			  }
			  g_depth=iteration;
			  nomore=(newpath.value>9000);
		  }
	  }
	} else // movestart<=mvs.amount
	{
		if (lastmovecheck)
		{
			path->move[depth].f=0;
			path->value=-10000+depth;
			return;
		} else
		{
			path->move[depth].f=0;
			path->value=0;
			return;
		}
	}
	for (child=movestart+1; child<=mvs.amount; child++)
	{
     nodes++;
	  process_mouse();
	  if (pressed==1)
	  {
		if (mousex>191 && mousex<191+55 && mousey>icony+4 && mousey<icony+4+12)
		{
		  options.whiteplayer=USER;
		  options.blackplayer=USER;
		  nomore=TRUE;
		  make_current=FALSE;
		} else
		if (mousex>256 && mousex<256+55 && mousey>icony+4 && mousey<icony+4+12)
		{
		  make_current=TRUE;
		  nomore=TRUE;
		}
		wait_till_released();
	  }
	  if (calcbound>=usebound)
	  {
		  check_time(&current);
		  goto done;
	  }
	  if (!nomore && no_check_position(pos,(legalmove=mvs.move[child]),&newpos))
	  {
		if (pos->mvr=='w') legalmove.check=check(&newpos,newpos.bking[0]); else legalmove.check=check(&newpos,newpos.wking[0]);
		if (depth==0)
		{
		  if (options.playstyle==FIXEDLEVEL && options.analysis)
		  {
			  maxbar=(options.maxdepth);
			  show_time_bar(child+((iteration-2)*mvs.amount), mvs.amount*(maxbar-1), (mainmover=='b'));
		  }
		  for (loop=0; loop<draws; loop++)
		  if (dontmove[loop].f==legalmove.f && dontmove[loop].f==legalmove.f && dontmove[loop].t==legalmove.t && dontmove[loop].t==legalmove.t)
		  {
			  newpath.value=0;
			  path->move[1].f=0;
			  current.move[0]=legalmove;
			  goto drawjump;
		  }
		} // if depth==0
		current.move[depth]=legalmove;
		minimax(&newpos,depth+1,-calcbound,-usebound,current,&newpath,legalmove.check,extend);
		newpath.value=-newpath.value;
drawjump:;
		if (newpath.value>calcbound && !nomore)
		{
		 calcbound=newpath.value;
		 bestpath=newpath;
		 bestpath.move[depth]=legalmove;
		 if (depth==0)
		 {
			if (options.analysis) showpath(260,&bestpath);
			g_depth=iteration;
			nomore=(newpath.value>9000);
		 }
		}
	  } // !nomore
	} // for child
done:
*path=bestpath;
path->value=calcbound;
} // function minimax
