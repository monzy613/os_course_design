#include "apilib.h"
#include <stdio.h>

 int rand();/*0 32767*/
 int planex=100;
 int planey=180; //plane��ʼ���� 
 int flag = 0;  //ֻ����һ��8��enenmy 
 void move(int win ,int i, int timer, char *keyflag);

    struct Enemy{   // ���ˣ���ʯ  @�� 
    	int x;
    	int y;   	
    }enemy[8];

void HariMain(void)
{
   
	int win, i;
	char buf[200 * 200];
	char keyflag[4];
	win = api_openwin(buf, 200, 200, -1, "plane");
	 start: 
	api_boxfilwin(win, 5, 25, 195, 195, 0);
	//struct Enemy *enemy = api_malloc(sizeof(struct Enemy));
	int s = 9999999;    //�����ٶ� 
	int timer;
	timer = api_alloctimer();
	api_inittimer(timer, 128);
	
	for (;;) {
		int e=0;
		if(flag == 0)
		{
		   for(e = 0;e < 8; e++)
		   {
		   	enemy[e].y = rand()/1310+25;
			enemy[e].x = rand()/173 + 3;		   
	       }
	       flag = 1;        //ֻ����һ�� 
	    }
	    

		for(e = 0; e<8;e++)
		{
			api_putstrwin(win,enemy[e].x, enemy[e].y, 0, 1, "@"); //�ú�ɫ���ǹ켣 
			enemy[e].y = enemy[e].y+5;	  //move down
			api_putstrwin(win,enemy[e].x, enemy[e].y, 3, 1, "@");  //��ʾ�ɻ���λ�� 
			
			if(enemy[e].y > 180)
			{
				api_putstrwin(win,enemy[e].x, enemy[e].y, 0, 1, "@");
				enemy[e].y = rand()/1310+25;
				enemy[e].x = rand()/173 + 3;
				if(s>99999)
				    {
					s = s - 99999 ;   //���� 
					} 
			}
			
			
			if(planex >enemy[e].x-20 && planex <enemy[e].x+3)            //�ж���ײ 
			 	if(planey >enemy[e].y-3 && planey <enemy[e].y+3)
			 {
			 	api_putstrwin(win , 100, 100, 1, 9, "GAME OVER");			 	
				 while(1)
				 {				 	 	
				   if (api_getkey(1) == 0x0a) 
				    {
				    goto start;
					} /* enter���¿�ʼ */
				}
			 }		
		}
				
		int t = 0; 
		for(t=0; t<s; t++){}   // ��ʯ�ٶȿ��ƣ�s�ݼ���ʯ���� 
		move(win,1, timer, keyflag);		
	}
	api_end();
}

void move(int win ,int i, int timer, char *keyflag)
{
	int j;
	if (i > 0) {
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
	    	if (planex > 5) {api_putstrwin(win, planex, planey, 0, 3, "^$^"); planex -= 5; }  //����켣 
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
	api_putstrwin(win, planex, planey, 3, 3, "^$^");   //��ӡ�ɻ���λ�� 
	return;
}

