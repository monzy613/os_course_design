#include "apilib.h"
#include "bootpack.h"

void HariMain(void)
{
	char *buf;
	int win;

	api_initmalloc();
	buf = api_malloc(150 * 150);
	win = api_openwin(buf, 150, 150, -1, "hello");
	api_boxfilwin(win,  8, 36, 141, 43, 6);
	api_putstrwin(win, 0, 0, 0, 12, "hello my world");
	for (;;) {
		if (api_getkey(1) == 0x0a) {
			break;
		}
	}
	api_end();
}
