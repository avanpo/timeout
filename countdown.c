#include <ncurses.h>

#include "countdown.h"

static short disp[11] = {
	075557, 011111, 071747, 071717,
	055711, 074717, 074757, 071111,
	075757, 075717, 002020
};

static long old[6], next[6], new[6], mask;

static void set(int t, int n);
static void standt(int on);

void draw_countdown(int seconds, int y, int x)
{
	int min = seconds / 60;
	int sec = seconds % 60;

	mask = 0;
	set(sec % 10, 0);
	set(sec / 10, 4);
	set(min % 10, 10);
	set(min / 10, 14);
	set (10, 7);

	long t, a;
	int i, j, s, k;

	if (min == 0) attron(A_BLINK);

	for (k = 0; k < 6; ++k) {
		new[k] = (new[k] & ~mask) | (next[k] & mask);
		next[k] = 0;
		for (s = 1; s >= 0; --s) {
			standt(s);
			for (i = 0; i < 6; ++i) {
				if ((a = (new[i] ^ old[i]) & (s ? new : old)[i]) != 0) {
					for (j = 0, t = 1 << 16; t; t >>= 1, ++j) {
						if (a & t) {
							if (!(a & (t << 1))) {
								move(y + i, x + 2 * j);
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

	if (min == 0) attroff(A_BLINK);
	
	refresh();
	move(COUNTDOWN_HEIGHT - 1, COUNTDOWN_LENGTH);
}

static void set(int t, int n)
{
	int i, m;

	m = 7 << n;
	for (i = 0; i < 5; ++i) {
		next[i] |= ((disp[t] >> (4 - i) * 3) & 07) << n;
		mask |= (next[i] ^ old[i]) & m;
	}

	if (mask & m) mask |= m;
}

static void standt(int on)
{
	if (on) {
		attron(A_STANDOUT);
	} else {
		attroff(A_STANDOUT);
	}
}
