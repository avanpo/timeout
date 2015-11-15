#include <stdio.h>
#include <stdlib.h>

#include "config.h"

struct config *load_config()
{
	FILE *fp = fopen("config", "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open config file.\n");
		exit(EXIT_FAILURE);
	}

	struct config *config = calloc(1, sizeof(struct config));

	char key[255];
	char value[255];

	int i;
	for (i = 0; fscanf(fp, "%s: %s", key, value) == 2; ++i) {
		
	}

	if (i != 2) {
		fprintf(stderr, "Config file malformed.\n");
		exit(EXIT_FAILURE);
	}

	return config;
}
