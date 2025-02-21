#ifdef _WIN32
#include <windows.h>
#else
#define _DEFAULT_SOURCE
#include <unistd.h>
#endif // _WIN32

void sleep_ms(int timems) {
#ifdef _WIN32
    Sleep(timems);
#else
    usleep(timems * 1000);
#endif // _WIN32
}
