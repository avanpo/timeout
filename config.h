#ifndef CONFIG_H
#define CONFIG_H

struct config {
	char fname[256];
	char lname[256];

	int stime;
};

struct config *load_config();

#endif
