#include "apilib.h"

struct DLL_STRPICENV {	/* 64KB */
	int work[64 * 1024 / 4];
};

struct RGB {
	unsigned char b, g, r, t;
};

/* bmp.nasm */
int info_BMP(struct DLL_STRPICENV *env, int *info, int size, char *fp);
int decode0_BMP(struct DLL_STRPICENV *env, int size, char *fp, int b_type, char *buf, int skip);

/* jpeg.c */
int info_JPEG(struct DLL_STRPICENV *env, int *info, int size, char *fp);
int decode0_JPEG(struct DLL_STRPICENV *env, int size, char *fp, int b_type, char *buf, int skip);

unsigned char rgb2pal(int r, int g, int b, int x, int y);
void error(char *s);

void HariMain(void)
{
	struct DLL_STRPICENV env;
	char filebuf[512 * 1024], winbuf[1040 * 805];
	char s[32], *p;
	int win, i, j, fsize, xsize, info[8];
	struct RGB picbuf[1024 * 768], *q;
	api_cmdline(s, 30);
	for (p = s; *p > ' '; p++) { }
	for (; *p == ' '; p++) { }
	i = api_fopen(p); if (i == 0) { error("file not found.\n"); }
	fsize = api_fsize(i, 0);
	if (fsize > 512 * 1024) {
		error("file too large.\n");
	}
	api_fread(filebuf, fsize, i);
	api_fclose(i);

	if (info_BMP(&env, info, fsize, filebuf) == 0) {
		if (info_JPEG(&env, info, fsize, filebuf) == 0) {
			api_putstr0("file type unknown.\n");
			api_end();
		}
	}



	api_end();




}



unsigned char rgb2pal(int r, int g, int b, int x, int y)
{
	static int table[4] = { 3, 1, 0, 2 };
	int i;
	x &= 1; 
	y &= 1;
	i = table[x + y * 2];	
	r = (r * 21) / 256;	
	g = (g * 21) / 256;
	b = (b * 21) / 256;
	r = (r + i) / 4;
	g = (g + i) / 4;
	b = (b + i) / 4;
	return 16 + r + g * 6 + b * 36;
}

void error(char *s)
{
	api_putstr0(s);
	api_end();
}
