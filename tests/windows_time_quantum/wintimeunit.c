/**
 * For mingw, compile with:
 *     gcc -g -Wall -Wpedantic .\wintimeunit.c -lwinmm
 */

/**
 * @file wintimeunit.c
 * @author michisei
 * @brief A small program to echo out the minimum time slice for Windows OS
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 * BSD Zero Clause License
 * 
 * Copyright (c) 2025 michisei
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#include <Windows.h>

int main(void) {
	TIMECAPS ptc;
	(void) timeGetDevCaps(&ptc, sizeof(ptc));

	(void) printf("wPeriodMin -> %u ms\n", ptc.wPeriodMin);
	(void) printf("wPeriodMax -> %u ms\n", ptc.wPeriodMax);

	return 0;
}
