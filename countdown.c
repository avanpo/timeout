#include <ncurses.h>
#include <unistd.h>

#define YBASE    10
#define XBASE    10
#define XLENGTH  54
#define YDEPTH   5

short disp[11] = {
	075557, 011111, 071747, 071717,
	055711, 074717, 074757, 071111,
	075757, 075717, 002020
};

long old[6], next[6], new[6], mask;

void set(int t, int n);
void standt(int on);

void run_countdown()
{
	long t, a;
	int i, j, s, k;
	int n = 0;

	int sec = 35;
	int min = 23;

	initscr();
	
	clear();
	refresh();

	do {
		char buf[30];

		mask = 0;
		
		set(sec % 10, 0);
		set(sec / 10, 4);
		set(min % 10, 10);
		set(min / 10, 14);
		set (10, 7);

		for (k = 0; k < 6; ++k) {
			new[k] = (new[k] & ~mask) | (next[k] & mask);
			next[k] = 0;
			for (s = 1; s >= 0; --s) {
				standt(s);
				for (i = 0; i < 6; ++i) {
					if ((a = (new[i] ^ old[i]) & (s ? new : old)[i]) != 0) {
						for (j = 0, t = 1 << 26; t; t >>= 1, ++j) {
							if (a & t) {
								if (!(a & (t << 1))) {
									move(YBASE + i, XBASE + 2 * j);
								}
								addstr("  ");
							}
						}
					}
					if (!s) {
						old[i] = new[i];
					}
				}
				if (!s) {
					refresh();
				}
			}
		}

		mvaddstr(16, 30, buf);

		move(6, 0);
		refresh();
		sleep(1);
		sec--;
		while (wgetch(stdscr) != ERR) continue;
	} while (--n);

	standend();
	clear();
	refresh();
	endwin();
}

void set(int t, int n)
{
	int i, m;

	m = 7 << n;
	for (i = 0; i < 5; ++i) {
		next[i] |= ((disp[t] >> (4 - i) * 3) & 07) << n;
		mask |= (next[i] ^ old[i]) & m;
	}

	if (mask & m) mask |= m;
}

void standt(int on)
{
	if (on) {
		attron(A_STANDOUT);
	} else {
		attroff(A_STANDOUT);
	}
}
