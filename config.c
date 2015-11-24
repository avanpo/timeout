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
	char value[2048] = {0};

	int i, j;

	for (i = 0; fscanf(fp, "%[^:\n]: %[^\n]\n", key, value) == 2; ++i) {
		int len = strlen(value);
		if (len >= 2048) len = 2047;

		if (strcmp(key, "first name") == 0 && len <= 256) {
			strncpy(conf->fname, value, len);
		}
		if (strcmp(key, "last name") == 0 && len <= 256) {
			strncpy(conf->lname, value, len);
		}
		if (strcmp(key, "start time") == 0) {
			conf->stime = (int)strtol(value, NULL, 10);
		}
		if (strcmp(key, "page") == 0) {
			conf->pages[conf->num_pages] = calloc(2048, sizeof(char));
			for (j = 0; j < len; ++j) {
				if (value[j] == '`') {
					conf->pages[conf->num_pages] = '\n';
				} else {
					conf->pages[conf->num_pages] = value[j];
				}
			}
			++conf->num_pages;
		}
		if (strcmp(key, "key") == 0) {
			for (j = 0; j < 16; ++j) {
				sscanf(value, "%02hhX ", &conf->key[j]);
			}
		}

		memset(key, 0, 256);
		memset(value, 0, 1024);
	}

	if (i < 5 || conf->num_pages < 1) {
		fprintf(stderr, "Config file malformed.\n");
		exit(EXIT_FAILURE);
	}

	return conf;
}
