#include <ncurses.h>
#include <string.h>

#include "state.h"

static void handle_input(struct state *st)
{
	int clen = strlen(st->input);

	if (clen == 0) {
		return;
	}
	strncpy(st->message, st->input, clen);
}

void accept_input(struct state *st)
{
	int y, x;
	getyx(stdscr, y, x);

	move(y, x + st->index);

	int ch;
	if ((ch = getch()) == ERR) {
		return;
	}
	
	if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
		if (st->index != 0) {
			--(st->index);

			st->input[st->index] = 0;
			move(y, x + st->index);
			addch(' ');
			move(y, x + st->index);
		}
	} else if (ch == 32) {
		if (st->index < 64) {
			addch(ch);
			++(st->index);
		}
	} else if ((ch >= 48 && ch < 58) || (ch >= 65 && ch < 91) ||
			(ch >= 97 && ch < 123)) {
		if (st->index < 64) {
			st->input[st->index] = ch;
			addch(ch);
			++(st->index);
		}
	} else if (ch == '\n') {
		mvaddstr(y, x, "                                                                ");
		move(y, x);
		memset(st->message, 0, 64);

		handle_input(st);

		memset(st->input, 0, 64);
		st->index = 0;
	}
}
