#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define quick_mul_10_unsigned(n) ((((n) << 2) + (n)) << 1)

int quick_mul_10_signed(int n) {
	if (n < 0) {
		n = quick_mul_10_unsigned(-n);
		return -(n & INT_MAX);
	}

	return quick_mul_10_unsigned(n) & INT_MAX;
}

int nomul_div_10_unsigned(int n) {
	// Using multiplicative inverse of 10 shifted left by 32 bits

	// The binary result of multiplicative inverse of 10 is
	//   00011001100110011001100110011001

	n += n >> 1;
	n >>= 4;

	n += n >> 4;
	n += n >> 8;
	n += n >> 16;

	n++; // Add one to correct for the fractional truncation

	return n;
}

int nomul_div_10_signed(int n) {
	if (n < 0) {
		n = nomul_div_10_unsigned(-n);
		return -n;
	}

	return nomul_div_10_unsigned(n);
}

void nomul_div_mod_10_signed(int* div_out, int* mod_out, int n) {
	int q = nomul_div_10_signed(n);

	if (div_out != NULL)
		*div_out = q;

	int b = nomul_mul_10_signed(q);

	if (b > n) {
		b -= 10;
	}

	if (mod_out != NULL)
		*mod_out = n - b;
}

int nomul_div_10_concept(int n) {
	uint64_t ln = n;

	ln *= 0x1999999a; // (Multiplicative inv of 10 << 32) + 1

	ln >>= 32;

	return (int) ln;
}

int main(void) {
	for (int i = 0, n = 1; i < 8; i++, n = quick_mul_10_signed(n)) {
		(void) printf("10 ^ %d -> %d\n", i, n);
	}
	
	for (int i = 0, n = -1; i < 8; i++, n = quick_mul_10_signed(n)) {
		(void) printf("-1 * 10 ^ %d -> %d\n", i, n);
	}

	(void) printf("%d / 10 -> %d\n", 20, nomul_div_10_signed(20));
	(void) printf("%d / 10 -> %d\n", 20, nomul_div_10_concept(20));
	(void) printf("%d / 10 -> %d\n", 90, nomul_div_10_signed(90));
	(void) printf("%d / 10 -> %d\n", 90, nomul_div_10_concept(90));
	(void) printf("%d / 10 -> %d\n", 120, nomul_div_10_signed(120));
	(void) printf("%d / 10 -> %d\n", 120, nomul_div_10_concept(120));
	
	for (int i = 0; i < 30; i++) {
		int mod;
		nomul_div_mod_10_signed(NULL, &mod, i);
		(void) printf("%d %% 10 -> %d\n", i, mod);
	}

	return 0;
}
