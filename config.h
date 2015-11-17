#ifndef CONFIG_H
#define CONFIG_H

struct config {
	char fname[256];
	char lname[256];

	int stime;

	char key[16];

	int num_pages;
	char *pages[16];
};

struct config *load_config();

#endif
