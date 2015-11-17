#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "countdown.h"
#include "draw.h"
#include "state.h"

#define WIDTH 100

static void draw_border(int size_y, int size_x, int time_left);

static void draw_info(int y, int x, struct state *st, struct config *conf)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	mvprintw(y + 1, x, "Welcome, %s %s", conf->fname, conf->lname);
	mvprintw(y + 1, x + WIDTH - 18, "%02d:%02d - %02d/%02d/%04d", tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year+ 1900);

	move(y + 2, x);
	int i;
	for (i = 0; i < WIDTH; ++i) {
		addch('-');
	}

	mvprintw(y + 4, x, "File: %1d/%1d", st->page, conf->pages);
}

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
	move(y, x);
	int i;
	for (i = 0; i < WIDTH; ++i) {
		addch('-');
	}
	mvaddstr(y + 2, x, "Please enter a command:");
	mvaddstr(y + 4, x, ">");
	mvaddstr(y + 6, x, "");
	move(y + 4, x + 2);
}

void draw_page(struct state *st, struct config *conf)
{
	int size_y, size_x;
	getmaxyx(stdscr, size_y, size_x);

	draw_border(size_y, size_x, st->time_left);

	draw_info(6, (size_x - WIDTH) / 2, st, conf);

	draw_key(20, size_x / 2 - 35);

	draw_countdown(st->time_left, 25, size_x / 2 - COUNTDOWN_LENGTH / 2);

	// this must be last, in order for the input function to
	// pick up the cursor position
	draw_input(40, (size_x - WIDTH) / 2);
}

static void draw_border(int size_y, int size_x, int time_left)
{
	srand(0);

	int width = (size_x - WIDTH - 10) / 2;
	int remainder = (size_x - WIDTH - 10) % 2;

	int i, j;
	for (i = 0; i < size_y; ++i) {
		if (i < 5 || i > 50) {
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
