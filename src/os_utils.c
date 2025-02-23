#ifdef _WIN32
#include <windows.h>
#else
#define _DEFAULT_SOURCE
#include <unistd.h>
#endif // _WIN32

#ifdef _WIN32
#define WIN_MIN_SLEEP_TIME 16
#endif // _WIN32

#include "os_utils.h"

void sleep_ms(int timems) {
#ifdef _WIN32
	if (timems < WIN_MIN_SLEEP_TIME) {
		sleep_us(timems * 1000);
	} else {
		Sleep(timems);
	}
#else
	usleep(timems * 1000);
#endif // _WIN32
}

void sleep_us(int timeus) {
#ifdef _WIN32
	// From 
	//  https://stackoverflow.com/questions/5801813/c-usleep-is-obsolete-workarounds-for-windows-mingw
	// 
	// WARNING: This may involve busy waiting
	// UPDATE:  No it doesn't
	HANDLE timer; 
	LARGE_INTEGER ft; 

	ft.QuadPart = -(10 * timeus); // Convert to 100 nanosecond interval,
	                              // negative value indicates relative time
	timer = CreateWaitableTimer(NULL, TRUE, NULL); 
	(void) SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
	(void) WaitForSingleObject(timer, timeus / 1000);
	(void) CloseHandle(timer); 
#else
	usleep(timeus);
#endif // _WIN32
}
