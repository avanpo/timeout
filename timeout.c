#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "countdown.h"

int main(int argc, char **argv)
{
	struct config *conf = load_config();

	run_countdown();

	return 0;
}
