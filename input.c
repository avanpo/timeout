#include <ncurses.h>
#include <string.h>

void handle_input(int *index, int *input)
{
	int y, x;
	getyx(stdscr, y, x);

	move(y, x + *index);

	int ch;
	if ((ch = getch()) == ERR) {
		return;
	}
	
	if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
		if (*index != 0) {
			--(*index);

			input[*index] = 0;
			move(y, x + *index);
			addch(' ');
			move(y, x + *index);
		}
	} else if (ch == 32 || (ch >= 48 && ch < 58) ||
			(ch >= 65 && ch < 91) ||
			(ch >= 97 && ch < 123)) {
		if (*index < 64) {
			input[*index] = ch;
			addch(ch);

			++(*index);
		}
	} else if (ch == '\n') {
		mvaddstr(y, x, "                                                                ");
		move(y, x);

		memset(input, 0, 64);
		*index = 0;
	}
}
