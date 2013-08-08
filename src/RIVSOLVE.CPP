#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "rivaldef.h"
#include "rivalchi.h"
#include "rivmouse.h"
#include "rivaldis.h"

extern char nomore, iteration, quiescence_depth, g_depth, draws, mainmover, make_current, no_more_openings;
extern gametype game;
extern struct postype current;
extern signed int pressed, mousex, mousey;
extern mvtype dontmove[];
extern long nodes, blacks, whites;
extern int maxbar;
extern optiontype options;
extern char centrality[];
extern void check_time(struct pathtype *path);
extern time_t starttime, newtime, oldtime;

extern void makemv(mvtype move);

void solveminimax(struct postype *pos, char depth, int usebound, int calcbound,struct pathtype current, struct pathtype *path, char lastmovecheck)
{
 register char child;
 register char loop;
 struct movelist mvs;
 struct pathtype bestpath, newpath;
 mvtype legalmove;
 struct postype newpos;
 char skipped;
 if (nomore) return;
 if (depth>quiescence_depth)
 {
	  oldtime=newtime;
	  if ((newtime=time(NULL)-starttime)>oldtime)
	  {
		if (mainmover=='b') blacks+=(newtime-oldtime); else whites+=(newtime-oldtime);
		if (options.analysis) showpath(195,&current);
		oldtime=newtime;
	  }
	  path->move[depth].f=0;
	  path->value=0;
	  current.move[depth].f=0;
	  current.value=path->value;
	  return;
 }
	mvs=get_children(pos);
	skipped=0;
	for (child=1; child<=mvs.amount; child++)
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
	  if (no_check_position(pos,(legalmove=mvs.move[child]),&newpos))
	  {
		if (pos->mvr=='w')
		{
		  legalmove.check=check(&newpos,newpos.bking[0]);
		} else
		{
		  legalmove.check=check(&newpos,newpos.wking[0]);
		}
		if (depth==iteration-2 && !legalmove.check) goto next;
		newpath.value=-1;
		if (depth==0)
		{
		 for (loop=0; loop<=draws; loop++)
		  if (dontmove[loop].f==legalmove.f && dontmove[loop].f==legalmove.f && dontmove[loop].t==legalmove.t && dontmove[loop].t==legalmove.t)
		  {
			newpath.value=0;
			path->move[1].f=0;
		  }
		  if (options.analysis) show_time_bar(child+((iteration-2)*mvs.amount), mvs.amount*7, (mainmover=='b'));
		}
		current.move[depth]=legalmove;
		if (newpath.value==-1)
		{
		  solveminimax(&newpos,depth+1,-calcbound,-usebound,current,&newpath,legalmove.check);
		  newpath.value=-newpath.value;
		}
		if (newpath.value>calcbound && !nomore)
		{
		  calcbound=newpath.value;
		  bestpath=newpath;
		  bestpath.move[depth]=legalmove;
		  if (depth==0)
		  {
			 nomore=(newpath.value>9000);
		  }
		}
		if (calcbound>=usebound)
		{
		  goto done;
		}
	  } //f==0;
	  else
	  skipped++;
next:   ;
	}
	if (mvs.amount==skipped)
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
done:
*path=bestpath;
path->value=calcbound;
}

void solvey(void)
{
  int i;
  struct pathtype curr,path;
  path.move[0].f=0;
  path.value=0;
  nomore=FALSE;
  for (i=0; i<=11; i++) curr.move[i].f=0;
  computer_move_displays();
  mainmover=current.mvr;
  show_blue_tiles();
  show_mouse();
  for (iteration=2; iteration<=8; iteration+=2)
  {
			 quiescence_depth=iteration-1;
			 solveminimax(&current,0,32700,-32700,curr,&path,FALSE);
			 if (path.value>9900)
			 {
				nomore=TRUE;
				SolveyBlank(iteration/2, 1);
				pressed=0;
				while (!pressed) process_mouse();
				if (pressed==1)
				{
					options.whiteplayer=USER;
					options.blackplayer=USER;
					if (mousex>=iconx+61) makemv(path.move[0]);
					nomore=TRUE;
				}
				break;
			 } else
			 {
				SolveyBlank(iteration/2, 0);
			 }
  }
  wait_till_released();
}
