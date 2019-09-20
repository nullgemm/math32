#ifndef H_MATH32
#define H_MATH32

#include <stdint.h>

// does not support 0 (brute-tested)
uint8_t zeros(uint32_t x);
// does not support 0xFFFFFFFF (brute-tested)
uint8_t ilog10(uint32_t x);
// does not support 0xFFFFFFFF (brute-tested)
uint8_t ilog2(uint32_t x);
// works as intended (brute-tested)
uint32_t isqrt(uint32_t x);
// works as intended (brute-tested)
int32_t icbrt(uint32_t x);
// seems to work as intended
// but check the number limits!
int32_t ipow(int32_t base, uint8_t exp);
// works as intended
uint32_t iatan2(int32_t x, int32_t y);
// works as intended
int32_t isin(int32_t x);
// works as intended
int32_t icos(int32_t x);

#endif
