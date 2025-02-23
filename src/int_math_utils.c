#include <limits.h>

#include "int_math_utils.h"

int nomul_mul_1000_unsigned(int n) {
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

	return n;
}

int nomul_mul_1000_signed(int n) {
	if (n < 0) {
		n = nomul_mul_1000_unsigned(-n);
		return -(n & INT_MAX);
	}

	return nomul_mul_1000_unsigned(n) & INT_MAX;
}

long nomul_mul_1000_unsigned_long(long n) {
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

	return n;
}

long nomul_mul_1000_signed_long(long n) {
	if (n < 0) {
		n = nomul_mul_1000_unsigned_long(-n);
		return -(n & LONG_MAX);
	}

	return nomul_mul_1000_unsigned_long(n) & LONG_MAX;
}
