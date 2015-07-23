#include "apilib.h"

#include <stdio.h>


void wait(int i, int timer, char *keyflag, char *last_direction);


void HariMain(void)
{


	char *buf;
	int win, i, x, y, timer;
	api_initmalloc();
	buf = api_malloc(200 * 200);
	char* title;
	char keyflag[4];
	char *last_direction;
	*last_direction = '4';
	sprintf(title, "hungry snake %d", last_key);
	win = api_openwin(buf, 200, 200, -1, title);
	timer = api_alloctimer();

	api_inittimer(timer, 128);

	api_boxfilwin(win, 5, 25, 195, 195, 0);
	 x = 75;
	 y =  55;
	api_putstrwin(win, x, y, 3, 1, "*");

	int foodX, foodY;
	foodX = 80;
	foodY = 80;

	for (;;) {
		//wait(1, timer, keyflag, last_direction);


		i = *lastdirection;
		api_putstrwin(win, x, y, 0, 1, "*");
		
		if (i == '4' && x >   5) { x -= 5; }
		if (i == '6' && x <= 185) { x += 5; }
		if (i == '8' && y >=  25) { y -= 5; }
		if (i == '2' && y <=  180) { y += 5; }
		if (i == 0x0a) { break; }
		api_putstrwin(win, x, y, 3, 1, "*");

		api_putstrwin(win, foodX, foodY, 4, 1, "+");
		
		int k = 0;
		for(;k < 75535512;k++) {
		}
		
		wait(1, timer, keyflag, last_direction);

	}


	api_closewin(win);
	api_end();
}


void wait(int i, int timer, char *keyflag, char *last_direction)
{
	int j;
	if (i > 0) {
		/* ˆê’èŽžŠÔ‘Ò‚Â */
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
			*last_direction = '4';
		}
		if (j == '6') {
			keyflag[1 /* right */] = 1;
			*last_direction = '6';
		}
		if (j == '8') {
			keyflag[2 /* up */] = 1;
			*last_direction = '8';
		}
		if (j == '2') {
			keyflag[3 /* down */] = 1;
			*last_direction = '2';
		}
		
	}
	return;
}
