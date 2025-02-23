#include <limits.h>

#include "int_math_utils.h"

// #define quick_mul_1000_signed(n) (((((n) << 10) - 24) & INT_MAX) | ((n) & (~INT_MAX)))

int quick_mul_1000_signed(int n) {
	int sign_bit = n & (~INT_MAX);

	// Prime factorization of 1000:
	//   2 * 2 * 2 * 5 * 5 * 5
	//   2^3 * 5 * 5 * 5

	// Multiply by 5 three times
	// n * 5 = n * 4 + n
	n = (n << 2) + n;
	n = (n << 2) + n;
	n = (n << 2) + n;

	// Multiply by 2 ^ 3
	n <<= 3;

	// Truncate result and restore the sign bit
	n = (n & INT_MAX) | sign_bit;

	return n;
}

long quick_mul_1000_signed_long(long n) {
	long sign_bit = n & (~LONG_MAX);

	// Prime factorization of 1000:
	//   2 * 2 * 2 * 5 * 5 * 5
	//   2^3 * 5 * 5 * 5

	// Multiply by 5 three times
	// n * 5 = n * 4 + n
	n = (n << 2) + n;
	n = (n << 2) + n;
	n = (n << 2) + n;

	// Multiply by 2 ^ 3
	n <<= 3;

	// Truncate result and restore the sign bit
	n = (n & LONG_MAX) | sign_bit;

	return n;
}
