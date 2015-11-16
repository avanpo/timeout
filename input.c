#include <ncurses.h>

void handle_input(int *index, int *input, int y, int x)
{
	int ch;
	if ((ch = getch()) == ERR) {
		return;
	}
	
	if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
		if (*index != 0) {
			--(*index);

			input[*index] = 0;
			move(y, x + *index);
			delch();
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
		
	}
}
