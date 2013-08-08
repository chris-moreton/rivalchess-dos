#include "mousey.h"
#include "rivalgrf.h"
#include "rivaldef.h"

extern optiontype options;
unsigned char mouseblank[12*16+2];

signed int mousex, mousey;
signed int relmousex,relmousey, oldmousex, oldmousey, pressed;

unsigned char pointer[162]=
{
10,16,
00,16,16,00,00,00,00,00,00,00,
00,16,23,16,00,00,00,00,00,00,
00,16,28,23,16,00,00,00,00,00,
00,16,28,30,23,16,00,00,00,00,
00,16,28,30,30,23,16,00,00,00,
00,16,28,30,30,30,23,16,00,00,
00,16,28,30,30,30,30,23,16,00,
00,16,28,30,30,30,19,18,16,00,
00,16,28,30,23,30,16,16,00,00,
00,16,25,19,16,30,23,16,00,00,
00,16,16,16,16,27,30,16,00,00,
00,00,00,00,00,16,30,23,16,00,
00,00,00,00,00,16,27,30,16,00,
00,00,00,00,00,00,16,30,22,16,
00,00,00,00,00,00,16,27,16,00,
00,00,00,00,00,00,00,16,00,00
};

void show_mouse(void)
{
  makesprite(mousex, mousey, mousex+11, mousey+15, mouseblank);
  sprxy(mousex,mousey,pointer,0);
  oldmousex=mousex;
  oldmousey=mousey;
}

void hide_mouse(void)
{
  super_sprxy(oldmousex, oldmousey, mouseblank);
}

void process_mouse(int xlim1=4, int ylim1=4, int xlim2=309, int ylim2=183)
{
	  relpos(&relmousex,&relmousey);
	  pressed=readmbutton();
	  if (relmousex==0 && relmousey==0) return;
	  mousex+=(relmousex*12/options.sensitivity);
	  mousey+=(relmousey*12/options.sensitivity);
	  if (mousex<xlim1) mousex=xlim1;
	  if (mousex>xlim2) mousex=xlim2;
	  if (mousey<ylim1) mousey=ylim1;
	  if (mousey>ylim2) mousey=ylim2;
	  if (oldmousex!=mousex || oldmousey!=mousey)
	  {
		 super_sprxy(oldmousex,oldmousey,mouseblank);
		 show_mouse();
	  }
}

void wait_till_released(void)
{
  char down;
  down=readmbutton();
  while (down) down=readmbutton();
}

void wait_till_pressed(void)
{
  char down;
  down=readmbutton();
  while (!down) down=readmbutton();
}

void initialise_mouse(void)
{
	initmouse();
}

char mouse_detected(void)
{
  char d;
  d=readmbutton();
  return(d>=0 && d<=2);
}


