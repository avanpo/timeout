#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

struct config *load_config()
{
	FILE *fp = fopen("config/config", "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open config file.\n");
		exit(EXIT_FAILURE);
	}

	struct config *conf = calloc(1, sizeof(struct config));

	char key[256] = {0};
	char value[4096] = {0};

	int i, j;

	for (i = 0; fscanf(fp, "%[^:\n]: %[^\n]\n", key, value) == 2; ++i) {
		int len = strlen(value);
		if (len >= 4096) len = 4095;

		if (strcmp(key, "first name") == 0 && len <= 256) {
			strncpy(conf->fname, value, len);
		}
		if (strcmp(key, "last name") == 0 && len <= 256) {
			strncpy(conf->lname, value, len);
		}
		if (strcmp(key, "start time") == 0) {
			conf->stime = (int)strtol(value, NULL, 10);
		}
		if (strcmp(key, "intro") == 0) {
			for (j = 0; j < len; ++j) {
				if (value[j] == '`') {
					conf->intro[j] = '\n';
				} else {
					conf->intro[j] = value[j];
				}
			}
		}
		if (strcmp(key, "encrypted") == 0) {
			conf->encrypted_page = (int)strtol(value, NULL, 10);
		}
		if (strcmp(key, "page") == 0) {
			conf->pages[conf->num_pages] = calloc(4096, sizeof(unsigned char));
			for (j = 0; j < len; ++j) {
				if (value[j] == '`') {
					conf->pages[conf->num_pages][j] = '\n';
				} else {
					conf->pages[conf->num_pages][j] = value[j];
				}
			}
			++conf->num_pages;
		}
		if (strcmp(key, "hint") == 0) {
			conf->hints[conf->num_hints] = calloc(64, sizeof(char));
			strncpy(conf->hints[conf->num_hints], value, len);
			++conf->num_hints;
		}
		if (strcmp(key, "key") == 0) {
			for (j = 0; j < 16; ++j) {
				sscanf(value + j * 3, "%02hhx ", &conf->key[j]);
			}
		}
		if (strcmp(key, "fail") == 0) {
			strncpy(conf->fail, value, len);
		}
		if (strcmp(key, "fail2") == 0) {
			strncpy(conf->fail2, value, len);
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
