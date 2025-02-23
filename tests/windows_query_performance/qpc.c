#include <stdio.h>

#include <Windows.h>

#define SLEEP_DUR_MS 0

int main(void) {
	LARGE_INTEGER counts_per_sec;

	// Quote from Microsoft
	// | On systems that run Windows XP or later, the function will always 
	// |  succeed and will thus never return zero.
	(void) QueryPerformanceFrequency(&counts_per_sec);

	LARGE_INTEGER counts_start;
	LARGE_INTEGER counts_end;

	(void) QueryPerformanceCounter(&counts_start);

	Sleep(SLEEP_DUR_MS);

	(void) QueryPerformanceCounter(&counts_end);

	long long nclocks_passed = counts_end.QuadPart - counts_start.QuadPart;
	long long counts_per_usec = counts_per_sec.QuadPart / 1000000;
	long long time_elapsed_us = nclocks_passed / counts_per_usec;

	(void) printf("Ticks per second: %lld\n", counts_per_sec.QuadPart);
	(void) printf("Ticks timestamp before win32's Sleep(%d): %lld\n", SLEEP_DUR_MS, counts_start.QuadPart);
	(void) printf("Ticks timestamp after win32's Sleep(%d): %lld\n\n", SLEEP_DUR_MS, counts_end.QuadPart);
	(void) printf("Ticks elapsed after win32's Sleep(%d): %lld\n\n", SLEEP_DUR_MS, counts_end.QuadPart - counts_start.QuadPart);
	(void) printf("Time elapsed after win32's Sleep(%d): %d\n\n", SLEEP_DUR_MS, (int) time_elapsed_us);

	return 0;
}
