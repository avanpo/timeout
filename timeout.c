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
struct state *init_state();

void begin(struct config *conf)
{
	int size_y, size_x, y, x;
	getmaxyx(stdscr, size_y, size_x);
	y = size_y / 2 - 5;
	x = size_x / 2 - 32;

	char str[32] = {0};

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

		if (strlen(str) == len && !strncicmp(conf->lname, str, strlen(conf->lname))) {
			break;
		} else {
			mvaddstr(y + 4, x, "unknown user");
		}
	}
}

int run(struct config *conf)
{
	time_t start, now;
	time(&start);

	struct state *st = init_state();
	st->time_total = conf->stime;

	while (1) {
		time(&now);
		st->time_left = st->time_total - (now - start);

		draw_page(st, conf);

		accept_input(st);

		millisleep(10);
	}
}

int main(int argc, char **argv)
{
	struct config *conf = load_config();

	initscr();
	init_window_simple();
	//begin(conf);

	init_window_main();
	run(conf);

	return 0;
}

void init_window_simple()
{
	nocbreak();
	echo();

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

struct state *init_state()
{
	struct state *st = calloc(1, sizeof(struct state));

	st->time_left = 0;
	st->page = 1;
	st->index = 0;
	
	return st;
}
