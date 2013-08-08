#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

#define maxmoves 300 // defined until stack implemented
#define maxmovelist 120
#define TRUE 1
#define FALSE 0
#define PROGRAM 0
#define USER 1
#define offx 5   /* board offset horizontal */
#define offy 5   /* board offset vertical */
#define iconx 185
#define icony  4
#define timex 212
#define timespace 6
#define SELECTER 43
#define BOOLEAN char
#define REGULARCHESS 1
#define KINGLET 2
#define GIVEAWAY 3
#define SHATRANJ 4
#define CHECKLESS 5
#define RETTAH 6
#define REGULARSET 0
#define HUMANSET 1
#define SHAPESET 2
#define SQUARE unsigned char
#define FIXEDLEVEL 1
#define FIXEDTIME 2
#define CHAMPIONSHIP 3
#define EQUALTIME 4
#define INFINITETIME 5
#define LOWSENS 26
#define MEDSENS 12
#define HISENS 6

struct postype
{
 char brd[100];  // 100
// char wlocs[16], blocs[16];
 char mvr;       // 100 + 1 = 101
// SQUARE whiteking, blackking; // 101 + 2 = 103
 char en_pawn, bmat, wmat;
// char bpieces, wpieces; // 103 + 5 = 108
 int total_bmat, total_wmat;
 unsigned char wrook1_moved;
 unsigned char wrook2_moved;
 unsigned char wking_moved;
 unsigned char brook1_moved;
 unsigned  char brook2_moved;
 unsigned  char bking_moved;
 unsigned  char white_castled;
 unsigned  char black_castled;
 char wrookcount, wbishcount, wqueencount, wpawncount, wknightcount, wkingcount;
 char brookcount, bbishcount, bqueencount, bpawncount, bknightcount, bkingcount;
 char wrook[8], brook[8], wbish[8], bbish[8], wpawn[8], bpawn[8], wqueen[8], bqueen[8], wknight[8], bknight[8], wking[8], bking[8];
};

typedef struct
{
 SQUARE f,t;   
 unsigned char lastwin;
 unsigned char check;
 unsigned char score;
} mvtype;

struct movelist
{
 unsigned char amount;
 mvtype move[maxmovelist];
};

struct pathtype
{
 int value;
 mvtype move[52];
};

struct gametype
{
  int movenum, lastmove;
  struct postype firstpos;
  mvtype previous_moves[maxmoves];
  long whites[maxmoves], blacks[maxmoves];
};

struct optiontype
{
  unsigned char blackplayer, whiteplayer;
  unsigned char maxdepth;
  unsigned int maxtime, champtime, champmoves;
  unsigned char library, analysis, inverted;
  unsigned char pubplay, deep_thought;
  unsigned char wo, bo, so;
  unsigned char game, chessset;
  unsigned char playstyle;
  unsigned char pieceslide;
  unsigned char sensitivity;
  unsigned char messages;
};

