#include "apilib.h"
#include <stdio.h>

int rand();/*0 32767*/
void wait(int win ,int i, int timer, char *keyflag);
    int planex=100;
    int planey=180;
    int flag = 0;
    
    struct Enemy{
    	int x;
    	int y;
    	
    }enemy[8];

void HariMain(void)
{
	int win, i;
	char buf[200 * 200];
	char keyflag[4];
	win = api_openwin(buf, 200, 200, -1, "test");
	api_boxfilwin(win, 5, 25, 195, 195, 0);
	
	//struct Enemy *enemy = api_malloc(sizeof(struct Enemy));
	
	int timer;
	timer = api_alloctimer();
	api_inittimer(timer, 128);
	
	for (;;) {
		int e=0;
		if(flag == 0)
		{
		   for(e = 0;e < 8; e++)
		   {
		   enemy[e].x = e*20+20;
		   enemy[e].y = 25;
		   
	       }
	       flag = 1;
	    }
	    

		for(e = 0; e<8;e++)
		{
			api_putstrwin(win,enemy[e].x, enemy[e].y, 0, 1, "@");
			enemy[e].y = enemy[e].y+5;	  //move down
			api_putstrwin(win,enemy[e].x, enemy[e].y, 3, 1, "@");
			
			if(enemy[e].y > 180){
				api_putstrwin(win,enemy[e].x, enemy[e].y, 0, 1, "@");
				enemy[e].y = 25;
			}
		
		}
		
		
		
		
		
		int t=0;
		
		for(t=0; t<9999999;t++){}   // wait.....
		

		wait(win,1, timer, keyflag);	
		
	}
	api_end();
}

void wait(int win ,int i, int timer, char *keyflag)
{
		
	
	int j;
	if (i > 0) {
		/* ˆê’èŽžŠÔ‘Ò‚�? */
		api_settimer(timer, i);
		i = 128;
	} else {
		i = 0x0a; /* Enter */
	}
	for (;;) {
		j = api_getkey(1);
		if (i == j) {
			break;
		}
		if (j == '4') {
			keyflag[0 /* left */]  = 1;
	    	if (planex > 5) {api_putstrwin(win, planex, planey, 0, 3, "^$^"); planex -= 5; }
		}
		if (j == '6') {
			keyflag[1 /* right */] = 1;
		    if (planex <= 185) {api_putstrwin(win, planex, planey, 0, 3, "^$^"); planex += 5; }
		}
		if (j == '8') {
			keyflag[2 /* up */] = 1;
     	    if (planey >=  25) {api_putstrwin(win, planex, planey, 0, 3, "^$^"); planey -= 5; }
		}
		if (j == '2') {
			keyflag[3 /* down */] = 1;
		    if ( planey <=  180) {api_putstrwin(win, planex, planey, 0, 3, "^$^"); planey += 5; }
		}		
	}
	api_putstrwin(win, planex, planey, 3, 3, "^$^");
	return;
}
