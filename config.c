#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

struct config *load_config()
{
	FILE *fp = fopen("config", "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open config file.\n");
		exit(EXIT_FAILURE);
	}

	struct config *conf = calloc(1, sizeof(struct config));

	char key[256] = {0};
	char value[1024] = {0};

	int i;

	for (i = 0; fscanf(fp, "%[^:\n]: %[^\n]\n", key, value) == 2; ++i) {
		int len = strlen(value);
		if (len >= 1024) len = 1023;

		if (strcmp(key, "first name") == 0) {
			strncpy(conf->fname, value, len);
		}
		if (strcmp(key, "last name") == 0) {
			strncpy(conf->lname, value, len);
		}
		if (strcmp(key, "start time") == 0) {
			conf->stime = (int)strtol(value, NULL, 10);
		}
		if (strcmp(key, "page") == 0) {
			conf->pages[conf->num_pages] = calloc(1024, sizeof(char));
			strncpy(conf->pages[conf->num_pages], value, len);
			++conf->pages;
		}

		memset(key, 0, 256);
		memset(value, 0, 1024);
	}

	if (i < 4 || conf->num_pages < 1) {
		fprintf(stderr, "Config file malformed.\n");
		exit(EXIT_FAILURE);
	}

	return config;
}
