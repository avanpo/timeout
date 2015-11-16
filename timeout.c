#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "countdown.h"
#include "input.h"
#include "utils.h"

void init_window_simple();
void init_window_main();

void begin(struct config *conf)
{
	int size_y, size_x, y, x;
	getmaxyx(stdscr, size_y, size_x);
	y = size_y / 2 - 5;
	x = size_x / 2 - 32;

	char str[32] = {0};

	move(y, x);
	print_str_slowly("please enter your last name");

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
	int time_total, time_left;
	time_t start, now;

	time(&start);
	time_total = conf->stime;

	int index = 0;
	int input[64] = {0};

	while (1) {
		time(&now);
		time_left = time_total - (now - start);

		draw_countdown(time_left, 0, 0);

		move(7, index);

		handle_input(&index, input, 7, 0);
	}
}

int main(int argc, char **argv)
{
	struct config *conf = load_config();

	initscr();
	init_window_simple();
	begin(conf);

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

	clear();
	refresh();
}
