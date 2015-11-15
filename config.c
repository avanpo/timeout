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

	struct config *config = calloc(1, sizeof(struct config));

	char key[256] = {0};
	char value[1024] = {0};

	int i;

	for (i = 0; fscanf(fp, "%[^:\n]: %[^\n]\n", key, value) == 2; ++i) {
		if (strcmp(key, "first name") == 0) {
			strncpy(config->fname, value, strlen(value));
		}
		if (strcmp(key, "last name") == 0) {
			strncpy(config->lname, value, strlen(value));
		}

		memset(key, 0, 256);
		memset(value, 0, 1024);
	}

	if (i != 2) {
		fprintf(stderr, "Config file malformed.\n");
		exit(EXIT_FAILURE);
	}

	return config;
}
