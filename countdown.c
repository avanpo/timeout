#include <ncurses.h>

#define COUNTDOWN_HEIGHT 5
#define COUNTDOWN_LENGTH 34

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
	refresh();
	move(COUNTDOWN_HEIGHT - 1, COUNTDOWN_LENGTH);
}

/*void run_countdown()
{
	long t, a;
	int i, j, s, k;

	time(&start);
	countdown = 1600;

	initscr();

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	
	clear();
	refresh();

	int index = 0;
	char input[1024] = {0};

	while (1) {
		mask = 0;
		time(&now);

		countdown = 1600 - (now - start);
		int min = countdown / 60;
		int sec = countdown % 60;

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
						for (j = 0, t = 1 << 16; t; t >>= 1, ++j) {
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

		move(10, index);
		refresh();

		int ch;
		if ((ch = getch()) != ERR) {
			if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
				if (index != 0) {
					index--;
					move(10, index);
					delch();
				}
			} else if (ch == 32 || (ch >= 48 && ch < 58) ||
					(ch >= 65 && ch < 91) || (ch >= 97 && ch < 123)) {
				index++;
				addch(ch);
			}
		}
		//sleep(1);
		//while (wgetch(stdscr) != ERR) continue;
	}

	standend();
	clear();
	refresh();
	endwin();
}*/

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
