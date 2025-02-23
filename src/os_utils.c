#ifdef _WIN32
#include <windows.h>
#else
#define _DEFAULT_SOURCE
#include <unistd.h>
#endif // _WIN32

#include "int_math_utils.h"

#include "os_utils.h"

#ifdef _WIN32
#define WIN_MIN_SLEEP_TIME 16

#define USECS_PER_SEC 1000000
static void win_usleep(int timeus) {
	LARGE_INTEGER counts_per_sec;

	// Quote from Microsoft
	// | On systems that run Windows XP or later, the function will always 
	// |  succeed and will thus never return zero.
	// https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency
	(void) QueryPerformanceFrequency(&counts_per_sec);

	LONGLONG counts_per_usec = counts_per_sec.QuadPart / USECS_PER_SEC;

	LARGE_INTEGER counts_start;
	LARGE_INTEGER counts_end;

	int time_elapsed_us = 0;

	(void) QueryPerformanceCounter(&counts_start);

	while (time_elapsed_us < timeus) {
		Sleep(0);
		(void) QueryPerformanceCounter(&counts_end);
		time_elapsed_us =
			(int) (
				(counts_end.QuadPart - counts_start.QuadPart) / counts_per_usec
			);
	}
}
#endif // _WIN32

void sleep_ms(int timems) {
#ifdef _WIN32
	if (timems > WIN_MIN_SLEEP_TIME) {
		int remainder_sleep_ms = timems % WIN_MIN_SLEEP_TIME;
		Sleep(timems - remainder_sleep_ms);
		win_usleep(quick_mul_1000_signed(remainder_sleep_ms));
	} else {
		win_usleep(quick_mul_1000_signed(timems));
	}
#else
	usleep(quick_mul_1000_signed(timems));
#endif // _WIN32
}

void sleep_us(int timeus) {
#ifdef _WIN32
	if (timeus > (WIN_MIN_SLEEP_TIME * 1000)) {
		int remainder_sleep_us = timeus % (WIN_MIN_SLEEP_TIME * 1000);
		Sleep((timeus - remainder_sleep_us) / 1000);
		win_usleep(remainder_sleep_us);
	} else {
		win_usleep(timeus);
	}
#else
	usleep(timeus);
#endif // _WIN32
}
