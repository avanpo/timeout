#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "draw.h"
#include "input.h"
#include "state.h"
#include "utils.h"

void init_window_simple();
void init_window_main();
struct state *init_state(struct config *conf);

void intro(struct config *conf)
{
	move(1, 0);
	printw(conf->intro);
	printw("\n\nPress enter to continue...\n\n");
	refresh();
	char str[1] = {0};
	getnstr(str, 0);
}

void begin(struct config *conf)
{
	int size_y, size_x, y, x;
	getmaxyx(stdscr, size_y, size_x);
	y = size_y / 2 - 5;
	x = size_x / 2 - 32;

	char str[32] = {0};

	clear();
	refresh();
	move(y, x);
	print_str_slowly("enter your last name to continue...");

	while (1) {
		move(y + 2, x);
		clrtoeol();
		addch('>');
		move(y + 2, x + 2);
		refresh();
		getnstr(str, 32);

		int len = strlen(conf->lname);

		if (strlen(str) == len && !strncicmp(conf->lname, str, len)) {
			break;
		} else if (strlen(str) <= 0) {
			move(y + 4, x);
			clrtoeol();
		} else {
			mvaddstr(y + 4, x, "unknown user");
		}
	}
}

void fail(struct config *conf)
{
	int size_y, size_x, y, x;
	getmaxyx(stdscr, size_y, size_x);
	y = size_y / 2 - 5;
	x = size_x / 2 - 32;

	mvprintw(y, x, conf->fail);
	mvprintw(y + 2, x, conf->fail2);
	curs_set(0);
	refresh();

	while (1) {
		millisleep(100000);
	}
}

int run(struct config *conf)
{
	time_t start, now;
	time(&start);

	struct state *st = init_state(conf);

	while (1) {
		if (!st->decrypted) {
			time(&now);
		}
		st->time_left = st->time_total - (now - start);

		if (st->time_left < 0) {
			return st->decrypted;
		}

		draw_page(st);

		accept_input(st);

		millisleep(10);
	}
}

int main(int argc, char **argv)
{
	struct config *conf = load_config();

	initscr();
	init_window_simple();
	//intro(conf);
	//begin(conf);

	init_window_main();
	int success = run(conf);

	init_window_simple();
	if (!success) {
		fail(conf);
	}

	endwin();
	return 0;
}

void init_window_simple()
{
	nocbreak();
	echo();
	nodelay(stdscr, FALSE);
	curs_set(1);

	clear();
	refresh();
}

void init_window_main()
{
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	clear();
	refresh();
}

struct state *init_state(struct config *conf)
{
	struct state *st = calloc(1, sizeof(struct state));

	st->conf = conf;

	st->time_total = conf->stime;
	st->num_pages = conf->num_pages;

	return st;
}
