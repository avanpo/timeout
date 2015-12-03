#ifndef CONFIG_H
#define CONFIG_H

struct config {
	char fname[256];
	char lname[256];

	int stime;

	unsigned char key[16];

	int num_pages;
	char *pages[32];

	int num_hints;
	char *hints[32];

	char fail[256];
	char fail2[256];
};

struct config *load_config();

#endif
