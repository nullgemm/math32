#ifndef C_TESTS
#define C_TESTS

#include "testoasterror.h"
#include "math32.h"

// does not test full zeroes
void test_zeros(struct testoasterror* test)
{
	uint32_t num;

	for (num = 0; num < 32; ++num)
	{
		testoasterror(test, zeros(0x80000000 >> num) == num);
	}
}

#endif
