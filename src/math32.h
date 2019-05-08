#ifndef H_MATH32
#define H_MATH32

#include <stdint.h>

uint8_t zeros(uint32_t x);
uint8_t ilog10(uint32_t x);
uint8_t ilog2(uint32_t x);
uint32_t isqrt(uint32_t x);
int32_t icbrt(uint32_t x);
int32_t ipow(int32_t base, uint8_t exp);

#endif
