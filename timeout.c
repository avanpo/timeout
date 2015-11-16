#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "countdown.h"
#include "input.h"

int run(struct config *conf)
{
	int time_total, time_left;
	time_t start, now;

	time(&start);
	time_total = conf->stime;

	initscr();

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	clear();
	refresh();

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

	run(conf);

	return 0;
}
