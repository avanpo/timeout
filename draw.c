#include <ncurses.h>
#include <stdlib.h>

#include "config.h"
#include "countdown.h"
#include "draw.h"

static void draw_border(int size_y, int size_x, int time_left);

static void draw_key(int y, int x)
{
	move(y, x);

	int i;
	addstr("key:");
	for (i = 0; i < 16; ++i) {
		printw("    ");
	}
	move(y + 1, x + 4);
	for (i = 0; i < 16; ++i) {
		if (!i) {
			printw("  --");
		} else {
			printw("----");
		}
	}
	move(y + 2, x + 4);
	for (i = 0; i < 16; ++i) {
		printw("  %02d", i + 1);
	}
}

static void draw_input(int y, int x)
{
	mvaddstr(y, x, "+-------------------------------------------------------------------+");
	mvaddstr(y + 1, x, "| Please enter a command:");
	mvaddstr(y + 1, x + 68, "|");
	mvaddstr(y + 2, x, "| >");
	mvaddstr(y + 2, x + 68, "|");
	mvaddstr(y + 3, x, "+-------------------------------------------------------------------+");
	move(y + 2, x + 4);
}

void draw_page(int time_left, struct config *conf)
{
	int size_y, size_x;
	getmaxyx(stdscr, size_y, size_x);

	draw_border(size_y, size_x, time_left);

	draw_key(20, size_x / 2 - 35);

	draw_countdown(time_left, 25, size_x / 2 - COUNTDOWN_LENGTH / 2);

	// this must be last, in order for the input function to
	// pick up the cursor position
	draw_input(35, size_x / 2 - 34);
}

static void draw_border(int size_y, int size_x, int time_left)
{
	srand(0);

	int width = (size_x - WIDTH) / 2;
	int remainder = (size_x - WIDTH) % 2;

	int i, j;
	for (i = 0; i < size_y; ++i) {
		if (i < 6 || i > 50) {
			move(i, 0);
			for (j = 0; j < size_x; ++j) {
				addch(rand() % 2 + 48);
			}
		} else {
			move(i, 0);
			for (j = 0; j < width; ++j) {
				addch(rand() % 2 + 48);
			}
			move(i, width + WIDTH);
			for (j = 0; j < width + remainder; ++j) {
				addch(rand() % 2 + 48);
			}
		}
	}
}
