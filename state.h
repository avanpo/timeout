#ifndef STATE_H
#define STATE_H

struct state {
	struct config *conf;

	int time_total;
	int time_left;
	int decrypted;
	int num_pages;
	int page;
	char message[64];

	unsigned char key[16];

	int index;
	char input[64];
};

#endif
