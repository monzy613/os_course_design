#include "apilib.h"
#include <stdio.h>

int * hanois[3];//�洢��ŵ��
int out_size = 0;//ץ�ŵ����Ӵ�С
int out_location = 0;//ץ�ŵ�λ��
int level = 3;
int step = 0;

void hanoi_init(int win)//��ʼ��
{
	out_size=0;
	out_location=0;
	step=0;
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		hanois[i] = (int *) api_malloc(level * 4);//�˴�malloc���䵥λ���ֽ�
		int j = 0;
		for (; j < level; j++)
		{
			hanois[i][j] = 0;
		}
	}//��ʼ����ŵ������

	for (i = 0; i < level; i++)
	{
		hanois[0][i] = level - i;
	}//����һ������
	hanoi_print(win);
}

void triangle_print(int win, int x0, int x1, int y)//����ױ����´�ӡ���ȱ�������
{
	while ((x1 - x0) > 0)
	{
		api_linewin(win, x0, y, x1, y, 1);
		x1--;
		x0++;
		y++;
	}
	api_refreshwin(win, 6, 26, 295, 193);
}

void item_print(int win, int x, int y, int size)//�����ά�������������Ӵ�С������ͼ��
{
	if (size == 0)return;
	else
	{
		int length = 14 + size * 8;
		int x0 = 90 * x + 56 - (length - 10) / 2;
		int y0 = 183 - 15 * y;
		int x1 = 90 * x + 66 + (length - 10) / 2;
		int y1 = 193 - 15 * y;
		api_boxfilwin(win, x0, y0, x1, y1, 1);
	}
}

void outitem_print(int win)//�����ⲿ����
{
	if (out_size == 0) return;
	else
	{
		int length = 14 + out_size * 8;
		int x0 = 90 * out_location + 56 - (length - 10) / 2;
		int y0 = 35;
		int x1 = 90 * out_location + 66 + (length - 10) / 2;
		int y1 = y0 + 10;
		api_boxfilwin(win, x0, y0, x1, y1, 1);
	}
}

void hanoi_print(int win)//���ݵ�ǰ����ȫ�ֱ�����������
{
	api_boxfilwin(win, 6, 26, 295, 193, 0);
	api_boxfilwin(win, 56, 53, 66, 193, 6);
	api_boxfilwin(win, 146, 53, 156, 193, 6);
	api_boxfilwin(win, 236, 53, 246, 193, 6);
	triangle_print(win, 56 + out_location * 90, 67 + out_location * 90, 28);
	char step_str[10];
	sprintf(step_str, "%d", step);
	api_putstrwin(win, 240, 26, 3, 8, step_str);

	outitem_print(win);
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		int j = 0;
		for (j = 0; j < level; j++)
		{
			item_print(win, i, j, hanois[i][j]);
			/*api_putchar(i + 48);
			api_putchar((int) ' ');
			api_putchar(j + 48);
			api_putchar((int) ' ');
			api_putchar(hanois[i][j] + 48);
			api_putchar((int) '\n');//�������*/
		}
	}
}

void hanoi_left(int win)
{
	if (out_location != 0)
	{
		out_location--;
		//step++;
		hanoi_print(win);
	}
	else return;
}

void hanoi_right(int win)
{
	if (out_location != 2)
	{
		out_location++;
		//step++;
		hanoi_print(win);
	}
	else return;
}

int hanoi_gettop(int i)//������������������һ�������� ��û�з���-1
{
	int j = level - 1;
	for (; j >= 0; j--)
	{
		if (hanois[i][j] > 0) return j;
	}
	return -1;
}

void hanoi_up(int win)
{
	if (out_size != 0) return;
	else
	{
		int j = hanoi_gettop(out_location);
		if (j == -1) return;
		else
		{
			out_size = hanois[out_location][j];
			hanois[out_location][j] = 0;
		}
		//step++;
		hanoi_print(win);
	}
}

void hanoi_down(int win)
{
	if (out_size == 0) return;
	else
	{
		int j = hanoi_gettop(out_location);
		if (j == -1)
		{
			hanois[out_location][0] = out_size;
			out_size = 0;
		}
		else if (hanois[out_location][j] > out_size)
		{
			hanois[out_location][j + 1] = out_size;
			out_size = 0;
		}
		else return;
		step++;
		hanoi_print(win);
	}
}

void hanoi_start(int win)
{
	int key;
	api_boxfilwin(win, 6, 26, 295, 193, 0);
	api_putstrwin(win, 30, 100, 3, 24, "please input the level:");
	api_putstrwin(win, 250, 100, 3, 24, "3 ");
	while (1)
	{
		key = api_getkey(1);
		api_boxfilwin(win, 6, 26, 295, 193, 0);
		api_putstrwin(win, 30, 100, 3, 24, "please input the level:");
		if (key == 10)
		{
			if (level >= 3 && level < 10)//level�Ϸ�
			{
				hanoi_init(win);
				break;
			}
			else continue;//���Ϸ�
		}
		else if (key > 50 && key < 58)
		{
			level = (key - 48);
			//api_putchar(10);
			char level_str[2];
			level_str[0] = level + 48;
			level_str[1] = 0;
			api_putstrwin(win, 250, 100, 3, 24, level_str);
		}
		else
		{
			char level_str[2];
			level_str[0] = level + 48;
			level_str[1] = 0;
			api_putstrwin(win, 250, 100, 3, 24, level_str);
		}
	}

	int winflag = 0;

	for (;;)
	{
		if (winflag == 1) break;
		key = api_getkey(1);
		switch (key)
		{
		case 50:
			hanoi_down(win);
			if (hanoi_gettop(2) == (level - 1))//ʤ������
			{
				winflag = 1;
			}
			break;
		case 52:
			hanoi_left(win);
			break;
		case 54:
			hanoi_right(win);
			break;
		case 56:
			hanoi_up(win);
			break;
		case 'q':
			api_closewin(win);
			api_end();
			break;
		}
	}

	api_boxfilwin(win, 6, 26, 295, 193, 0);
	api_putstrwin(win, 30, 100, 3, 8, "YOU WIN!");

	char step_str[10];
	sprintf(step_str, "%d", step);
	api_putstrwin(win, 100, 100, 3, 8, step_str);
	level=3;
}

void HariMain(void)
{
	char *buf;
	int win;
	api_initmalloc();
	buf = api_malloc(300 * 200);
	win = api_openwin(buf, 300, 200, -1, "hanoi");
	hanoi_start(win);
	for (;;)
	{
		int key;
		key = api_getkey(1);
		if(key == 0x0a) hanoi_start(win);
	}
	api_closewin(win);
	api_end();
}

