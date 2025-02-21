#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

static int is_parsable_int(const char* s) {
	if (s == NULL) {
		return 0;
	}
	return *s >= 48 && *s < 58;
}

void print_usage_info(const char* arg0) {
	(void) fprintf(stderr, "usage: %s [options] [file]...\n", arg0);
	(void) fprintf(stderr, 
		"A more simplified and slower tool that mimicks "
		"the behaviout of cat. It does not retain the "
		"full functionalities of the original tool.\n\n"
	);
	(void) fprintf(stderr, "Options:\n");
	(void) fprintf(stderr, "  -h, --help  display this help and exit.\n");
	(void) fprintf(stderr, "  -d, --delay specify delay for each character in milliseconds.\n");
}

static void __cpy_pos_args(char** pos_args_out, int argc, char** argv) {
	int i;
	for (i = 0; i < argc; i++) {
		pos_args_out[i] = argv[i];
	}
	pos_args_out[i] = NULL;
}

int parse_opts(options_t* opts_out, char** pos_args_out, int argc, char** argv) {
	int n_pos_args = 0;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--") == 0) {
			__cpy_pos_args(pos_args_out + n_pos_args, argc - i - 1, argv + i + 1);
			return 0;
		}

		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_usage_info(argv[0]);
			return 1;
		}

		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delay") == 0) {
			if (argc <= i + 1) {
				fprintf(stderr, "[\033[1;31mERROR\033[0m] Missing argument for %s.", argv[i]);
				return -1;
			}
			if (!is_parsable_int(argv[i + 1])) {
				fprintf(stderr, "[\033[1;31mERROR\033[0m] Expecting a number for %s.", argv[i]);
				return -1;
			}

			opts_out -> char_delay = atoi(argv[i + 1]);
			i++;
			continue;
		}

		pos_args_out[n_pos_args++] = argv[i];
	}
	pos_args_out[n_pos_args] = NULL;
	return 0;
}
