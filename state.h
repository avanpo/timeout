#ifndef STATE_H
#define STATE_H

struct state {
	int time_total;
	int time_left;
	int page;
	char message[64];

	int index;
	int input[64];
};

#endif
