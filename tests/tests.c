#ifndef C_TESTS
#define C_TESTS

#include "testoasterror.h"
#include "math32.h"
#include <math.h>
#include <stdio.h>

// does not test full zeroes
void test_zeros(struct testoasterror* test)
{
	uint32_t num;

	for (num = 0; num < 32; ++num)
	{
		testoasterror(test, zeros(0x80000000 >> num) == num);
	}
}

// does not test full ones
void test_ilog10(struct testoasterror* test)
{
	uint32_t num = 1;

	do
	{
		if (ilog10(num) != floor(log10(num)))
		{
			testoasterror_fail(test);
		}

		++num;
	}
	while(num < 0xFFFFFFFF);

	testoasterror(test, 1);
}

// does not test full ones
void test_ilog2(struct testoasterror* test)
{
	uint32_t num = 1;

	do
	{
		if (ilog2(num) != floor(log2(num)))
		{
			testoasterror_fail(test);
		}

		++num;
	}
	while(num < 0xFFFFFFFF);

	testoasterror(test, 1);
}

// tests everything
void test_isqrt(struct testoasterror* test)
{
	uint32_t num = 0;

	do
	{
		if (isqrt(num) != floor(sqrt(num)))
		{
			testoasterror_fail(test);
		}

		++num;
	}
	while(num != 0);

	testoasterror(test, 1);
}

// tests everything
void test_icbrt(struct testoasterror* test)
{
	uint32_t num = 0;
	uint32_t r;

	do
	{
		r = icbrt(num);
		if (r != floor(cbrt(num)))
		{
			// floating-point cbrts underestimate integer results
			// so we really need to double check any "failure"...
			if ((r * r * r) != num)
			{
				testoasterror_fail(test);
			}
		}

		++num;
	}
	while(num != 0);

	testoasterror(test, 1);
}

// very limited test
void test_ipow(struct testoasterror* test)
{
	uint8_t num = 0;

	do
	{
		if (ipow(3, num) != floor(pow(3, num)))
		{
			testoasterror_fail(test);
		}

		++num;
	}
	while(num < 20);

	testoasterror(test, 1);
}

#endif
