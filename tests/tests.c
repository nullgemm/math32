#ifndef C_TESTS
#define C_TESTS

#include "testoasterror.h"
#include "math32.h"
#include <math.h>

#define M_PI 3.14159265358979323846

int64_t abs64(int64_t x)
{
	return (x < 0) ? -x : x;
}

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

// tests everything
void test_ipow(struct testoasterror* test)
{
	int32_t num = 0xFFFFFFF;
	int32_t max = num;
	uint8_t exp;

	int64_t real;

	do
	{
		exp = 0;
		real = floor(pow(num, exp));

		do
		{
			if (ipow(num, exp) != real)
			{
				testoasterror_fail(test);
			}

			++exp;

			real = floor(pow(num, exp));
		}
		while ((abs64(real) < 0x7FFFFFFF) && (exp != 0));

		++num;
	}
	while(num > max);

	testoasterror(test, 1);
}

// empiric test
void test_iatan2(struct testoasterror* test)
{
	int32_t x;
	int32_t y;
	int32_t ret;

	for (int32_t angle = 0; angle < 0x8000; ++angle)
	{
		x = 10000 * cos((angle * 2 * M_PI) / 0x8000);
		y = 10000 * sin((angle * 2 * M_PI) / 0x8000);
		ret = iatan2(x, y);

		if (abs64(ret - angle) > 1)
		{
			testoasterror_fail(test);
		}
	}

	testoasterror(test, 1);
}

void test_isin(struct testoasterror* test)
{
	for (double i = 0; i < 32768; ++i)
	{
		if (abs64((sin(i * (2 * M_PI) / 32768.0) * 4096) - isin(i)) > 12)
		{
			testoasterror_fail(test);
		}
	}
}

void test_icos(struct testoasterror* test)
{
	for (double i = 0; i < 32768; ++i)
	{
		if (abs64((cos(i * (2 * M_PI) / 32768.0) * 4096) - icos(i)) > 12)
		{
			testoasterror_fail(test);
		}
	}
}

#endif
