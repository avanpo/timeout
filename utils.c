#include <ctype.h>
#include <ncurses.h>
#include <time.h>

int strncicmp(const char *a, const char *b, size_t n)
{
	int i, d;
	for (i = 0; i < n; ++i) {
		d = tolower(a[i]) - tolower(b[i]);
		if (d != 0) return d;
	}
	return 0;
}

void millisleep(int ms)
{
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (long)(ms % 1000) * 1000000L;

	nanosleep(&ts, NULL);
}

void print_str_slowly(const char *str)
{
	for (; *str; str++) {
		addch(*str);
		refresh();
		millisleep(100);
	}
}
