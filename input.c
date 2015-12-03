#include <ncurses.h>
#include <string.h>

#include "config.h"
#include "state.h"
#include "utils.h"

static void handle_input(struct state *st)
{
	int clen = strlen(st->input);

	if (clen == 0) {
		return;
	} else if (clen == 4 && strncicmp(st->input, "next", 4) == 0) {
		++st->page;
		st->page %= st->num_pages;
	} else if (clen == 4 && strncicmp(st->input, "prev", 4) == 0) {
		--st->page;
		if (st->page < 0) st->page = st->num_pages - 1;
	} else if (clen == 3 && strncicmp(st->input, "key", 3) == 0) {
		unsigned char i, n = 255, byte = 0;
		sscanf(st->input + 4, "%hhu", &n);
		for (i = 5; st->input[i - 1]; ++i);
		int byte_read = sscanf(st->input + i, "%02hhX", &byte);
		
		if (n > 0 && n <= 16 && byte_read == 1) {
			st->key[n - 1] = byte;
		} else if (n <= 0 || n > 16) {
			strcpy(st->message, "That byte does not exist.");
		} else {
			strcpy(st->message, "Incorrect byte format.");
		}
	} else if (clen == 7 && strncicmp(st->input, "decrypt", 7) == 0) {
		int i, j, incorrect;
		char msg[64] = {0};
		j = sprintf(msg, "Incorrect key bytes at position(s)");
		for (i = 0, incorrect = 0; i < 16; ++i) {
			if (st->key[i] != st->conf->key[i]) {
				j += sprintf(msg + j, " %02d", i + 1);
				++incorrect;
			}
		}
		sprintf(msg + j, ".");

		if (incorrect) {
			st->time_total -= 15;
			strcpy(st->message, msg);
		} else {
			st->decrypted = 1;
			strcpy(st->message, "File successfully decrypted.");
		}
	} else if (clen == 4 && strncicmp(st->input, "hint", 4) == 0) {
		int n;
		sscanf(st->input + 5, "%d", &n);

		if (n > 0 && n <= st->conf->num_hints) {
			strcpy(st->message, st->conf->hints[n - 1]);
		} else {
			strcpy(st->message, "That hint does not exist.");
		}
	} else {
		strcpy(st->message, "Unknown command.");
	}
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
