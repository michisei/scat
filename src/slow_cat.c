#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"
#include "os_utils.h"

#ifndef DEFAULT_DELAY_MS
#define DEFAULT_DELAY_MS 10
#endif // DEFAULT_DELAY_MS

#ifndef READ_BUFFER_SIZE
#define READ_BUFFER_SIZE 1048576
#endif // READ_BUFFER_SIZE

int perform_scat(const char* fn, int delay) {
	FILE* f;
	char buf[READ_BUFFER_SIZE];
	if (fn == NULL || strcmp(fn, "-") == 0) {
		f = stdin;
	} else {
		f = fopen(fn, "r");
	}
	if (f == NULL) {
		fprintf(stderr, 
			"[\033[1;33mWARNING\033[0m] Could not open file '%s': %s\n"
		, fn, strerror(errno));
		return 1;
	}

	size_t n_read;
	(void) setvbuf(stdout, NULL, _IONBF, 0);
	do {
		n_read = fread(buf, sizeof(char), READ_BUFFER_SIZE, f);
		for (int i = 0; i < n_read; i++) {
			(void) putc(buf[i], stdout);
			sleep_ms(delay);
		}
	} while (n_read == READ_BUFFER_SIZE);

	(void) setvbuf(stdout, NULL, _IOLBF, 0); // Sorry for non-tty stdouts :(

	if (fn != NULL && strcmp(fn, "-") != 0) {
		(void) fclose(f);
	}
	return 0;
}

int main(int argc, char** argv) {
	options_t opts = {
		.char_delay = DEFAULT_DELAY_MS
	};
	char* pos_args[argc + 1];
	pos_args[0] = NULL;

	int r = parse_opts(&opts, pos_args, argc, argv);
	if (r == 1)
		return 0;
	if (r < 0)
		return 1;

	if (pos_args[0] == NULL) {
		(void) perform_scat(NULL, opts.char_delay);
		return 0;
	}

	for (char** i = pos_args; *i != NULL; i++) {
		(void) perform_scat(*i, opts.char_delay);
	}
	return 0;
}