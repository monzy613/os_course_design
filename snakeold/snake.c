#include "apilib.h"
#include "../haribote/bootpack.h"
#include <stdio.h>






int snakeLength = 1;
int moveScale = 7;

struct snakeNode {
	int posX;
	int posY;
	int moveDirection;//4left 6right 8up 2down
	struct snakeNode *preNode;
	struct snakeNode *nextNode;
};


struct Food {
	int posX;
	int posY;
	int isEaten;
};


void nodeMover(struct snakeNode *node);
struct snakeNode *addSegment(struct snakeNode *tail, int* snakeLength);
void updateSnake(struct snakeNode *tail);
void changeDirection(struct snakeNode *head, int newDirection);
void scrnRefresher(int win, struct snakeNode *tail, int color, char *c);
void wait(int i, int timer, char *keyflag, char *last_direction, struct snakeNode *snakeHead);

int rand();/*0~32767*/
void foodInit(struct Food *food, int win, int color, char *c);
void detecting(struct snakeNode *head, struct snakeNode **tail, struct Food *food);
void delay();


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


	//snake
	struct snakeNode *head = api_malloc(sizeof(struct snakeNode));
	head->preNode = NULL;
	head->posX = 75;
	head->posY = 55;
	head->moveDirection = 4;

	struct snakeNode *tail = head;
	//snake

	//food
	struct Food food;
	food.posX = 69;
	food.posY = 61;
	food.isEaten = 1;// not eaten;
	//food



	sprintf(title, "posX: %d, posY: %d, mp: %d", tail->posX, tail->posY, tail->moveDirection);
	//sprintf(title, "Hungry Snake");
	win = api_openwin(buf, 200, 200, -1, title);
	timer = api_alloctimer();

	api_inittimer(timer, 128);

	api_boxfilwin(win, 5, 25, 195, 195, 0);
	x = 75;
	y = 55;
	tail->posX = 75;
	tail->posY = 55;
	api_putstrwin(win, tail->posX, tail->posY, 3, 1, "*");
	//scrnRefresher(win, tail, 3, "*");





	for (;;) {

		i = *last_direction;
		scrnRefresher(win, tail, 0, "*");
		// updateSnake(head);
		updateSnake(tail);
		scrnRefresher(win, tail, 3, "*");

		//add food here
		foodInit(&food, win, 4, "+");
		//add food here


		/*detecting*/
		detecting(head, &tail, &food);



		delay();
		//if (snakeLength < 10) {tail = addSegment(tail, &snakeLength);}

		wait(1, timer, keyflag, last_direction, head);
	}




	api_closewin(win);
	api_end();
}

void delay() {
		int k = 0;
		for(;k < 75535512; k++) {
		}	
}


void detecting(struct snakeNode *head, struct snakeNode **tail, struct Food *food) {
	if ((head->posX - food->posX) * (head->posX - food->posX) 
		+ 
		(head->posY - food->posY) * (head->posY - food->posY) <= 20) {
		*tail = addSegment(*tail, &snakeLength);
		food->isEaten = 1;
	} else {
		/*do nothing*/
	}
}



void scrnRefresher(int win, struct snakeNode *tail, int color, char *c) {
	//api_putstrwin(win, tail->posX, tail->posY, 0, 1, "*");
	while(tail != NULL) {
		api_putstrwin(win, tail->posX, tail->posY, color, 1, c);
		tail = tail->preNode;
	}

}







void nodeMover(struct snakeNode *node) {
	// move one distance on the current moving direction
	//  old move code
	// 	if (i == '4' && tail->posX > 5) { tail->posX -= 5;}
	// 	if (i == '6' && tail->posX <= 185) { tail->posX += 5; }
	// 	if (i == '8' && tail->posY >=  25) { tail->posY -= 5; }
	// 	if (i == '2' && tail->posY <=  180) { tail->posY += 5; }
	// 	if (i == 0x0a) { break; }	
	
	int movDir = node->moveDirection;
	switch(movDir) {
		case 4:{
			if (node->posX > 5) { 
				node->posX -= moveScale;
			}
			break;
		}
		case 6:{
			if (node->posX <= 185) { 
				node->posX += moveScale; 
			}
			break;
		}
		case 8:{
			if (node->posY >=  25) { 
				node->posY -= moveScale; 
			}
			break;
		}
		case 2:{
			if (node->posY <=  180) { 
				node->posY += moveScale; 
			}
			break;
		}
	}
	if (node->preNode != NULL) {
		node->moveDirection = node->preNode->moveDirection;
	}
}


struct snakeNode *addSegment(struct snakeNode *tail, int* snakeLength) {
	struct snakeNode *newTail = api_malloc(sizeof(struct snakeNode));
	tail->nextNode = newTail;
	newTail->preNode = tail;
	newTail->nextNode = NULL;
	int movDir = newTail->moveDirection = newTail->preNode->moveDirection;
	switch(movDir) {
		case 4:{
			newTail->posX = newTail->preNode->posX + moveScale;
			newTail->posY = newTail->preNode->posY;
			break;
		}
		case 6:{
			newTail->posX = newTail->preNode->posX - moveScale;
			newTail->posY = newTail->preNode->posY;
			break;
		}
		case 8:{
			newTail->posX = newTail->preNode->posX;
			newTail->posY = newTail->preNode->posY - moveScale;			
			break;
		}
		case 2:{
			newTail->posX = newTail->preNode->posX;
			newTail->posY = newTail->preNode->posY + moveScale;			
			break;
		}
	}
	(*snakeLength)++;
	return newTail;
}


void updateSnake(struct snakeNode *tail) {
	while(tail != NULL) {
		nodeMover(tail);
		tail = tail->preNode;
	}
}


// void updateSnake(struct snakeNode *head) {
// 	while(head != NULL) {
// 		nodeMover(head);
// 		head = head->nextNode;
// 	}
// }

void changeDirection(struct snakeNode *head, int newDirection) {
	head->moveDirection = newDirection;
}






void wait(int i, int timer, char *keyflag, char *last_direction, struct snakeNode *snakeHead)
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
			*last_direction = '4';
			changeDirection(snakeHead, 4);
		}
		if (j == '6') {
			keyflag[1 /* right */] = 1;
			*last_direction = '6';
			changeDirection(snakeHead, 6);
		}
		if (j == '8') {
			keyflag[2 /* up */] = 1;
			*last_direction = '8';
			changeDirection(snakeHead, 8);
		}
		if (j == '2') {
			keyflag[3 /* down */] = 1;
			*last_direction = '2';
			changeDirection(snakeHead, 2);
		}
		
	}
	return;
}

int range(int low, int high) {
	/*including high and low*/
	int returnValue = (rand() % (high - low + 1)) + low;
	return returnValue;
}




	/* old move code
		if (i == '4' && tail->posX > 5) { tail->posX -= 5;}
		if (i == '6' && tail->posX <= 185) { tail->posX += 5; }
		if (i == '8' && tail->posY >=  25) { tail->posY -= 5; }
		if (i == '2' && tail->posY <=  180) { tail->posY += 5; }
		if (i == 0x0a) { break; }	
	*/

void foodInit(struct Food *food, int win, int color, char *c) {
	/*
	position should be start at (75, 55) 
	and with(moveScale * n, moveScale * n) distance
	and 
	9 <= x <= 183, 9 + 6 * 29 = 183 => n(0~29)
	25 <= y <= 175, 25 + 6 * 25 = 175 => m(0~25)
	*/
	if (food->isEaten == 0) {
		/*not eaten*/
	} else {
		api_putstrwin(win, food->posX, food->posY, 0, 1, c);
		food->posX = 9 + 6 * range(0, 29);
		food->posY = 25 + 6 * range(0, 25);
		api_putstrwin(win, food->posX, food->posY, color, 1, c);
		food->isEaten = 0;
	}
}