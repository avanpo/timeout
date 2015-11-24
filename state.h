#ifndef STATE_H
#define STATE_H

struct state {
	int time_total;
	int time_left;
	int num_pages;
	int page;
	char message[64];

	char *key;

	int index;
	char input[64];
};

#endif
