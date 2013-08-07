#include <stdlib.h>
#include "rivaldef.h"
#include "rivalchi.h"
#include "rivmouse.h"
#include "rivaldis.h"

extern char nomore, iteration, quiescence_depth, g_depth, draws, mainmover, make_current;
extern signed int pressed, mousex, mousey;
extern mvtype dontmove[];
extern long nodes;
extern int maxbar;
extern optiontype options;
extern char centrality[];
extern void check_time(struct pathtype *path);

int kinglet_evaluate(struct postype *pos, char depth)
{
	register char squareindex;
	int pawnval;
	SQUARE sq;
	register int material=0;
	if (mainmover=='w') pawnval=200; else pawnval=200;
	char i;
	nodes++;
	material=pos->total_wmat-pos->total_bmat;

	for (i=0; i<=pos->wpawncount; i++)
  {
			squareindex=pos->wpawn[i];
			if (pos->brd[squareindex-1]=='P' && pos->brd[squareindex+11]=='P') material-=12;
			if (pos->brd[squareindex+1]=='P' && pos->brd[squareindex+11]=='P') material-=10;
			if (pos->brd[squareindex+1]=='P' && pos->brd[squareindex+10]=='P') material-=7;
			if (pos->brd[squareindex+2]=='P' && pos->brd[squareindex+11]=='P') material-=10;
			if (pos->wmat<14) material+=((squareindex%10)*abs((pos->bking[0]/10)-squareindex/10));
  }
  for (i=0; i<=pos->bpawncount; i++)
  {
			squareindex=pos->bpawn[i];
			if (pos->brd[squareindex+1]=='p' && pos->brd[squareindex-11]=='p') material+=12;
			if (pos->brd[squareindex-1]=='p' && pos->brd[squareindex-11]=='p') material+=10;
			if (pos->brd[squareindex-1]=='p' && pos->brd[squareindex-10]=='p') material+=7;
			if (pos->brd[squareindex-2]=='p' && pos->brd[squareindex-11]=='p') material+=10;
			if (pos->bmat<14)	material-=((9-squareindex%10)*abs((pos->wking[0]/10)-squareindex/10));
  }
  for (i=0; i<=pos->wrookcount; i++)
  {
			squareindex=pos->wrook[i];
			sq=10+(squareindex%10); // start search at left of board;
			pos->brd[squareindex]='-';
			if (pos->brd[sq]=='R' || pos->brd[sq+10]=='R' || pos->brd[sq+20]=='R' || pos->brd[sq+30]=='R' ||
								  pos->brd[sq+40]=='R' || pos->brd[sq+50]=='R' || pos->brd[sq+60]=='R' || pos->brd[sq+70]=='R')
									  material+=8;
			sq=(squareindex-(squareindex%10))+1; // start search at bottom of board;
			if (pos->brd[sq]=='R' || pos->brd[sq+1]=='R' || pos->brd[sq+2]=='R' || pos->brd[sq+3]=='R' ||
					 pos->brd[sq+4]=='R' || pos->brd[sq+5]=='R' || pos->brd[sq+6]=='R' || pos->brd[sq+7]=='R')
						  material+=8;
			if (pos->brd[sq+1]!='P' && pos->brd[sq+2]!='P' && pos->brd[sq+3]!='P' &&
								  pos->brd[sq+4]!='P' && pos->brd[sq+5]!='P' && pos->brd[sq+6]!='P')
									  material+=8;
			pos->brd[squareindex]='R';
			if (squareindex>70) material+=22;
  }
  for (i=0; i<=pos->brookcount; i++)
  {
			squareindex=pos->brook[i];
			sq=10+(squareindex%10); // start search at left of board;
			pos->brd[squareindex]='-';
			if (pos->brd[sq]=='r' || pos->brd[sq+10]=='r' || pos->brd[sq+20]=='r' || pos->brd[sq+30]=='r' ||
								  pos->brd[sq+40]=='r' || pos->brd[sq+50]=='r' || pos->brd[sq+60]=='r' || pos->brd[sq+70]=='r')
									  material-=8;
							 sq=(squareindex-(squareindex%10))+1; // start search at bottom of board;
			if (pos->brd[sq]=='r' || pos->brd[sq+1]=='r' || pos->brd[sq+2]=='r' || pos->brd[sq+3]=='r' ||
								  pos->brd[sq+4]=='r' || pos->brd[sq+5]=='r' || pos->brd[sq+6]=='r' || pos->brd[sq+7]=='r')
										material-=8;
			if (pos->brd[sq+1]!='p' && pos->brd[sq+2]!='p' && pos->brd[sq+3]!='p' &&
								  pos->brd[sq+4]!='p' && pos->brd[sq+5]!='p' && pos->brd[sq+6]!='p')
									  material-=8;
			pos->brd[squareindex]='r';
			if (squareindex<30) material-=22;
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
  }
  for (i=0; i<=pos->bqueencount; i++)
  {
			squareindex=pos->bqueen[i];
  }
  for (i=0; i<=pos->wbishcount; i++)
  {
			squareindex=pos->wbish[i];
			for (sq=squareindex; pos->brd[sq=sq-11]!='['; material+=((pos->brd[sq]!='P') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq+11]!='['; material+=((pos->brd[sq]!='P') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq-9]!='['; material+=((pos->brd[sq]!='P') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq+9]!='['; material+=((pos->brd[sq]!='P') ? 1 : 0));
			if (squareindex<20) material-=11;
  }
  for (i=0; i<=pos->bbishcount; i++)
  {
			squareindex=pos->bbish[i];
			for (sq=squareindex; pos->brd[sq=sq-11]!='['; material-=((pos->brd[sq]!='p') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq+11]!='['; material-=((pos->brd[sq]!='p') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq-9]!='['; material-=((pos->brd[sq]!='p') ? 1 : 0));
			for (sq=squareindex; pos->brd[sq=sq+9]!='['; material-=((pos->brd[sq]!='p') ? 1 : 0));
			if (squareindex>80) material+=11;
  }

  if (!pos->black_castled && pos->bking_moved) material+=9;
  if (!pos->white_castled && pos->wking_moved) material-=9;


	if (pos->wpawncount==-1)
	{
		if (pos->mvr=='w') return (-10000+depth); else return (10000-depth);
	} else
	{
		material+=(pawnval*pos->wpawncount);
	}
	if (pos->bpawncount==-1)
	{
		  if (pos->mvr=='b') return (-10000+depth); else return (10000-depth);
	} else
	{
		 material-=(pawnval*pos->bpawncount);
	}
	return (pos->mvr=='w') ? material : -material;
} // function kinglet evaluate

void kinglet_quiesce_evaluate(struct postype *pos, char depth, int usebound, int calcbound, struct pathtype current, struct pathtype *path)
{
  register char child;
  struct movelist mvs;
  struct pathtype bestpath, newpath;
  mvtype legalmove;
  struct postype newpos;
  if (nomore) return;
  if (depth>quiescence_depth)
  {
	path->move[depth].f=0;
	current.move[depth].f=0;
	path->value=kinglet_evaluate(pos,depth);
	current.value=path->value;
	return;
  }
  if ((calcbound=kinglet_evaluate(pos,depth))>=usebound)
  {
	 path->value=calcbound;
	 return;
  }
  bestpath.move[depth].f=0; // null move
  mvs=q_get_children(pos);
  for (child=1; child<=mvs.amount; child++)
  {
	  if (calcbound>=usebound)
	  {
		 *path=bestpath;
		 path->value=calcbound;
		 check_time(&current);
       return;
     }
     if (!nomore)
	  {
		 legalmove=mvs.move[child];
       alter(pos,legalmove,&newpos);
		 current.move[depth]=legalmove;
       kinglet_quiesce_evaluate(&newpos,depth+1,-calcbound,-usebound,current,&newpath);
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
				 nomore=(newpath.value>9900);
			 }
		 }
	  } // !nomore
  } // for child
*path=bestpath;
path->value=calcbound;
}

void kinglet_minimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char extend)
{
 register char child;
 register char loop;
 struct movelist mvs;
 struct pathtype bestpath, newpath;
 mvtype legalmove;
 struct postype newpos;
 if (nomore) return;
 if (depth>=iteration+extend)
 {
	path->move[depth].f=0;
	current.move[depth].f=0;
	kinglet_quiesce_evaluate(pos, depth, usebound, calcbound, current, &newpath);
	path->value=current.value=newpath.value;
	return;
 }
	mvs=get_children(pos);
	legalmove=mvs.move[1];
	alter(pos,legalmove,&newpos);
	if (depth==0)
	{
	  for (loop=0; loop<draws; loop++)
	  if (dontmove[loop].f==legalmove.f && dontmove[loop].f==legalmove.f && dontmove[loop].t==legalmove.t && dontmove[loop].t==legalmove.t)
	  {
		  newpath.value=0;
		  path->move[1].f=0;
		  current.move[0]=legalmove;
		  goto drawjumpother;
	  }
	}
	current.move[depth]=legalmove;
	kinglet_minimax(&newpos,depth+1,-calcbound,-usebound,current,&newpath,extend);
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
		  nomore=(newpath.value>9900);
		}
	}
	for (child=2; child<=mvs.amount; child++)
	{
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
	  if (!nomore)
	  {
		 legalmove=mvs.move[child];
		 alter(pos,legalmove,&newpos);
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
		 }
		 current.move[depth]=legalmove;
		 kinglet_minimax(&newpos,depth+1,-calcbound,-usebound,current,&newpath,extend);
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
			  nomore=(newpath.value>9900);
			}
		 }
	  } // !nomore
	} // for child
done:
*path=bestpath;
path->value=calcbound;
}
