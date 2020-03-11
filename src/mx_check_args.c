#include "ush.h"

void mx_check_args(char *line) {
	int m = 0;
	struct winsize sz;
	int d = mx_strlen(line);

	ioctl(0, TIOCGWINSZ, &sz);
	m = sz.ws_col - 5;
	if (m < d)
		fprintf(stderr, "ush: UZNAT NAZVANIE OSHIBKI + дореализовать(реализован только вывод)\n");
}
