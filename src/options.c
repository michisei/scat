#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "options.h"

static int is_parsable_int(const char* s) {
	if (s == NULL) {
		return 0;
	}
	return *s >= 48 && *s < 58;
}

#ifndef SCAT_VER
#define SCAT_VER "version 0.1"
#endif // SCAT_VER

const char* usage_info_fmt = 
	"usage: %s [options] [file]...\n"
	"A more simplified and slower tool that mimics the behaviour of the cat "
	"command.\n"
	"The tool will print characters one by one with a specified delay.\n"
	"It does not retain the full functionalities of the original tool.\n"
	"\n"
	"Options:\n"
	"  -h, --help  display this help and exit.\n"
	"  -d, --delay specify delay for each character in milliseconds.\n"
	"              For C edition only: You can specify three decimal places "
	              "for the delay for microsecond precision.\n"
	"              Note that the actual timing may not be accurate.\n"
	"\n"
	"scat C edition, " SCAT_VER ".\n";

void print_usage_info(const char* arg0) {
	(void) fprintf(stderr, usage_info_fmt, arg0);
}

static void __cpy_pos_args(char** pos_args_out, int argc, char** argv) {
	int i;
	for (i = 0; i < argc; i++) {
		pos_args_out[i] = argv[i];
	}
	pos_args_out[i] = NULL;
}

#define DECIMAL_RADIX 10
#define ASCII_DOT 46
#define ASCII_0 48
#define ASCII_9_PLUS_1 58
#define is_digit_char(c) ((c) >= ASCII_0 && (c) < ASCII_9_PLUS_1)
#define parsable_3dp_char(c) ((c) == ASCII_DOT || is_digit_char(c))

char* overflow_gag_lines[] = {
	"You wouldn't want to wait for 35 minutes for a single character.. right?",
	"Why would you want to wait for 35 minutes per character?",
	"Don't you have something better to do than waiting 35 minutes to print "
	"the next character?",
	"Looks like somebody have no life over here..",
	"Do you have nothing better to do?",
	"Encik's grandmother can write faster at this rate.."
};
int n_overflow_gag_lines = sizeof(overflow_gag_lines) / sizeof(char*);

#define DELAY_LIMIT 0x7fffffff
#define OVERFLOW_LINE                                                            \
    (void) fprintf(stderr,                                                       \
        "[\033[1;33mWARNING\033[0m] Delay given is limited to %d microseconds. " \
        "%s\n"                                                                   \
    , DELAY_LIMIT, overflow_gag_lines[rand() % n_overflow_gag_lines])

static int parse_3dp_decimal(const char* numstr) {
	char* int_stop_ptr;
	long r = strtol(numstr, &int_stop_ptr, DECIMAL_RADIX);

	if (r < 0) {
		return 0;
	}
	
	if (r > DELAY_LIMIT / 1000 || errno == ERANGE) {
		OVERFLOW_LINE;
		return DELAY_LIMIT;
	}

	r *= 1000;

	if (*int_stop_ptr == '.') {
		char dp_3[4] = "000";
		(void) strncpy(dp_3, int_stop_ptr + 1, 3 * sizeof(const char));
		for (int i = 0; i < 3; i++) {
			if (!is_digit_char(dp_3[i]))
				dp_3[i] = '0';
		}
		dp_3[3] = '\0';
		int inc = atoi(dp_3);
		int sum = r + inc;
		if ((sum & (~INT_MAX)) != 0) {
			OVERFLOW_LINE;
			return DELAY_LIMIT;
		}
		r = sum;
	}

	return (int) r;
}

int parse_opts(options_t* opts_out, char** pos_args_out, int argc, char** argv) {
	int n_pos_args = 0;
	srand(time(NULL));
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
			if (argv[i + 1][0] == '-') {
				(void) fprintf(stderr,
					"[\033[1;33mWARNING\033[0m] Sorry we have not invented the time "
					"machine yet...\n"
				);
				return 0;
			}
			if (!is_parsable_int(argv[i + 1])) {
				fprintf(stderr, "[\033[1;31mERROR\033[0m] Expecting a number for %s.", argv[i]);
				return -1;
			}

			// opts_out -> char_delay = atoi(argv[i + 1]);
			opts_out -> char_udelay    = parse_3dp_decimal(argv[i + 1]);
			opts_out -> char_delay     = opts_out -> char_udelay / 1000;
			opts_out -> char_udelay   -= opts_out -> char_delay * 1000;
			opts_out -> use_usec_delay = opts_out -> char_udelay != 0;
			i++;
			continue;
		}

		pos_args_out[n_pos_args++] = argv[i];
	}
	pos_args_out[n_pos_args] = NULL;
	return 0;
}
