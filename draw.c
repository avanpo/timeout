#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "countdown.h"
#include "draw.h"
#include "state.h"

#define WIDTH  100
#define HEIGHT 44
#define BASE_Y 7

static int size_y, size_x, page_y, page_x;

static void draw_line(int y);
static void draw_blank_line(int y);
static void draw_border(int time_left);

static void draw_info(int y, int x, struct state *st, struct config *conf)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	mvprintw(y, x, "Welcome, %s %s", conf->fname, conf->lname);
	mvprintw(y, x + WIDTH - 18, "%02d:%02d - %02d/%02d/%04d", tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year+ 1900);

	draw_line(y + 1);
}

static void draw_page_content(int y, int x, struct state *st, struct config *conf)
{
	int l, i, j, len = strlen(conf->pages[st->page]);
	for (i = 0; i < HEIGHT - 22; ++i) {
		draw_blank_line(y + i);
	}

	mvprintw(y, x, "File: %d/%d", st->page + 1, conf->num_pages);

	for (l = 0, i = 0; i < len; ++l) {
		for (j = 0; j < WIDTH && i < len; ++i, ++j) {
			if (conf->pages[st->page][i] == '\n') {
				++i;
				break;
			}
			mvaddch(y + 2 + l, x + j, conf->pages[st->page][i]);
		}
	}
}

static void draw_key(int y, int x, struct state *st)
{
	int i;
	mvprintw(y, x, "%02x", st->key[0]);
	for (i = 1; i < 16; ++i) {
		printw("  %02x", st->key[i]);
	}
	mvprintw(y + 1, x, "--");
	for (i = 1; i < 16; ++i) {
		printw("----");
	}
	mvprintw(y + 2, x, "01");
	for (i = 1; i < 16; ++i) {
		printw("  %02d", i + 1);
	}
}

static void draw_goal(int y, int x, struct state *st)
{
	draw_line(y);
	mvaddstr(y + 2, x, "To access encrypted files, enter the encryption key using the");
	mvaddstr(y + 3, x, "command \"key [DIGIT] [KEY_BYTE]\". When the key is complete,");
	mvaddstr(y + 4, x, "enter \"decrypt\" to decrypt the files.");
	mvaddstr(y + 6, x, "WARNING: An invalid key speeds up the self destruct sequence!");
	draw_key(y + 8, x, st);
	mvaddstr(y + 1, x + WIDTH - COUNTDOWN_LENGTH, "==================================");
	draw_countdown(st->time_left, y + 4, x + WIDTH - COUNTDOWN_LENGTH);
	mvaddstr(y + 11, x + WIDTH - COUNTDOWN_LENGTH, "==================================");
}

static void draw_input(int y, int x, struct state *st)
{
	draw_line(y);
	mvaddstr(y + 2, x, "Please enter a command:");
	mvaddstr(y + 4, x, ">");
	mvaddstr(y + 6, x, "                                                                ");
	mvaddstr(y + 6, x, st->message);
	move(y + 4, x + 2);
}

void draw_page(struct state *st)
{
	getmaxyx(stdscr, size_y, size_x);
	page_y = BASE_Y;
	page_x = (size_x - WIDTH) / 2;

	draw_border(st->time_left);

	draw_info(page_y, page_x, st, st->conf);

	draw_page_content(page_y + 3, page_x, st, st->conf);

	draw_goal(page_y + HEIGHT - 19, page_x, st);

	// this must be last, in order for the input function to
	// pick up the cursor position
	draw_input(page_y + HEIGHT - 7, page_x, st);
}

static void draw_line(int y)
{
	move(y, page_x);
	int i;
	for (i = 0; i < WIDTH; ++i) {
		addch('=');
	}
}

static void draw_blank_line(int y)
{
	move(y, page_x);
	int i;
	for (i = 0; i < WIDTH; ++i) {
		addch(' ');
	}
}

static void draw_border(int time_left)
{
	srand(0);

	int width = (size_x - WIDTH - 10) / 2;
	int remainder = (size_x - WIDTH - 10) % 2;

	int i, j;
	for (i = 0; i < size_y; ++i) {
		if (i < page_y - 2 || i > page_y + HEIGHT + 1) {
			move(i, 0);
			for (j = 0; j < size_x; ++j) {
				addch(rand() % 2 + 48);
			}
		} else {
			move(i, 0);
			for (j = 0; j < width; ++j) {
				addch(rand() % 2 + 48);
			}
			move(i, width + WIDTH + 10);
			for (j = 0; j < width + remainder; ++j) {
				addch(rand() % 2 + 48);
			}
		}
	}
}
