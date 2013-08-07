/*
  gnuchess.h - Header file for GNU CHESS

  Revision: 1990-04-18

  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.

  This file is part of CHESS.

  CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY.  No author or distributor accepts responsibility to anyone for
  the consequences of using it or for whether it serves any particular
  purpose or works at all, unless he says so in writing.  Refer to the CHESS
  General Public License for full details.

  Everyone is granted permission to copy, modify and redistribute CHESS, but
  only under the conditions described in the CHESS General Public License.
  A copy of this license is supposed to have been given to you along with
  CHESS so you can know your rights and responsibilities.  It should be in a
  file named COPYING.  Among other things, the copyright notice and this
  notice must be preserved on all copies.
*/

#include <stdio.h>
#define SEEK_SET 0
#define SEEK_END 2

#if !defined(__STDC__) || !defined(MSDOS)
#define const
#endif

#ifndef __GNUC__
#define inline
#endif

/*
  ttblsz must be a power of 2.
  Setting ttblsz 0 removes the transposition tables.
*/
#ifdef MSDOS
#define ttblsz (1 << 11)
#else
#define ttblsz (1 << 16)
#define huge
#endif /* MSODS */

#define maxdepth 30
#define white 0
#define black 1
#define neutral 2
#define no_piece 0
#define pawn 1
#define knight 2
#define bishop 3
#define rook 4
#define queen 5
#define king 6
#define bpawn 7
#define pmask 0x0007
#define promote 0x0008
#define cstlmask 0x0010
#define epmask 0x0020
#define exact 0x0040
#define pwnthrt 0x0080
#define check 0x0100
#define capture 0x0200
#define draw 0x0400
#define maxdepth 30
#define false 0
#define true 1
/* #define absv(x) ((x) < 0 ? -(x) : (x)) */

#define valueP 100
#define valueN 350
#define valueB 355
#define valueR 550
#define valueQ 1100
#define valueK 1200
#define ctlP 0x4000
#define ctlN 0x2800
#define ctlB 0x1800
#define ctlR 0x0400
#define ctlQ 0x0200
#define ctlK 0x0100
#define ctlBQ 0x1200
#define ctlBN 0x0800
#define ctlRQ 0x0600
#define ctlNN 0x2000
#define Patak(c, u) (atak[c][u] > ctlP)
#define Anyatak(c, u) (atak[c][u] > 0)

#if ttblsz
#define truescore 0x0001
#define lowerbound 0x0002
#define upperbound 0x0004
#define kingcastle 0x0008
#define queencastle 0x0010

struct hashval
{
  unsigned long key,bd;
};
struct hashentry
{
  unsigned long hashbd;
  unsigned short mv;
  unsigned char flags, depth;   /* char saves some space */
  short score;
#ifdef HASHTEST
  unsigned char bd[32];
#endif /* HASHTEST */

};

#ifdef HASHFILE
/*
  persistent transposition table.
  The size must be a power of 2. If you change the size,
  be sure to run gnuchess -t before anything else.
*/
#define frehash 6
#ifdef MSDOS
#define filesz (1 << 11)
#else
#define filesz (1 << 17)
#endif /* MSDOS */
struct fileentry
{
  unsigned char bd[32];
  unsigned char f, t, flags, depth, sh, sl;
};
/*
  In a networked enviroment gnuchess might be compiled on different
  hosts with different random number generators, that is not acceptable
  if they are going to share the same transposition table.
*/

unsigned int urand (void);
void srand (unsigned int seed);

#else
int rand (void);
void srand ( unsigned int seed);
#define urand rand
#endif /* HASHFILE */

extern unsigned long hashkey, hashbd;
/*extern struct hashval hashcode[2][7][64];*/
extern struct hashval far *hashcode;

/*extern struct hashentry huge ttable[2][ttblsz];*/
extern struct hashentry far *ttable;

#endif /* ttblsz */


extern HWND hComputerColor;
extern HWND hComputerMove;
extern HWND hWhosTurn;
extern HWND hClockComputer;
extern HWND hClockHuman;
extern HWND hMsgComputer;
extern HWND hMsgHuman;
extern HWND hStats;



struct leaf
{
  short f, t, score, reply;
  unsigned short flags;
};
struct GameRec
{
  unsigned short gmove;
  short score, depth, time, piece, color;
  long nodes;
};
struct TimeControlRec
{
  short moves[2];
  long clock[2];
};

struct BookEntry
{
  struct BookEntry far *next;
  unsigned short far *mv;
};

struct flags
{
  short mate;		/* the game is over */
  short post;		/* show principle variation */
  short quit;		/* quit/exit gnuchess */
  short reverse;	/* reverse board display */
  short bothsides;	/* computer plays both sides */
  short hash;		/* enable/disable transposition table */
  short force;		/* enter moves */
  short easy;		/* disable thinking on opponents time */
  short beep;		/* enable/disable beep */
  short timeout;	/* time to make a move */
  short rcptr;		/* enable/disable recapture heuristics */
};

/* extern struct leaf Tree[2000], *root; */
extern struct leaf far *Tree, far *root;

extern short TrPnt[maxdepth];
extern short board[64], color[64];
extern short PieceList[2][16], PawnCnt[2][8];
extern short castld[2], Mvboard[64];
extern short svalue[64];
extern struct flags flag;
extern short opponent, computer, Awindow, Bwindow, INCscore;
extern short dither, player;
extern short xwndw, epsquare, contempt;
extern long ResponseTime, ExtraTime, Level, et, et0, time0, ft;
extern long NodeCnt, ETnodes, EvalNodes, HashCnt, HashCol;
/* extern struct GameRec GameList[512];*/
extern struct GameRec far *GameList;

extern short GameCnt, Game50;
extern short Sdepth, MaxSearchDepth;
/*extern struct BookEntry *Book;*/
extern struct BookEntry far *Book;

extern struct TimeControlRec TimeControl;
extern short TCflag, TCmoves, TCminutes, OperatorTime;
extern const short otherside[3];
/*
extern const short otherside[3];
extern const short Stboard[64];
extern const short Stcolor[64];
*/
extern unsigned short hint, PrVar[maxdepth];

/*#define distance(a,b) distdata[a][b]*/
#define distance(a,b) *(distdata+a*64+b)

#define row(a) ((a) >> 3)
#define column(a) ((a) & 7)
#define locn(a,b) (((a) << 3) | b)
/*extern short distdata[64][64];*/
extern short far *distdata;

