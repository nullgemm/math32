#include "math32.h"
#include <stdint.h>

// BITS

static const uint8_t zeros_lut[64] =
{
	32, 20, 19, -1, -1, 18, -1,  7,
	10, 17, -1, -1, 14, -1,  6, -1,
	-1,  9, -1, 16, -1, -1,  1, 26,
	-1, 13, -1, -1, 24,  5, -1, -1,
	-1, 21, -1,  8, 11, -1, 15, -1,
	-1, -1, -1,  2, 27,  0, 25, -1,
	22, -1, 12, -1, -1,  3, 28, -1,
	23, -1,  4, 29, -1, -1, 30, 31,
};

uint8_t zeros(uint32_t x)
{
   x = x | (x >> 1);
   x = x | (x >> 2);
   x = x | (x >> 4);
   x = x | (x >> 8);
   x = x & ~(x >> 16);

   x = (x << 9) - x;
   x = (x << 11) - x;
   x = (x << 14) - x;

   return zeros_lut[x >> 26];
}

// LOG

static const uint32_t ilog10_lut[32] =
{
	-1U, -1U, 1000000000U,
	-1U, -1U, 100000000U,
	-1U, -1U, 10000000U, -1U,
	-1U, -1U, 1000000U,
	-1U, -1U, 100000U,
	-1U, -1U, 10000U, -1U,
	-1U, -1U, 1000U,
	-1U, -1U, 100U,
	-1U, -1U, 10U, -1U,
	-1U, -1U,
};

uint8_t ilog10(uint32_t x)
{
	uint32_t z = zeros(x);

	return (31 - z) * 77 / 256 + (x >= ilog10_lut[z]);
}


static const uint8_t ilog2_lut[32] =
{
	 0,  9,  1, 10, 13, 21,  2, 29,
	11, 14, 16, 18, 22, 25,  3, 30,
	 8, 12, 20, 28, 15, 17, 24,  7,
	19, 27, 23,  6, 26,  5,  4, 31,
};

uint8_t ilog2(uint32_t x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return ilog2_lut[(x * 0x07C4ACDD) >> 27];
}

// ROOTS

uint32_t isqrt(uint32_t x)
{
	uint32_t x1;
	int32_t s;
	int32_t g0;
	int32_t g1;

	if (x <= 1)
	{
		return x;
	}

	s = 1;
	x1 = x - 1;

	if (x1 > 65535)
	{
		s = s + 8;
		x1 = x1 >> 16;
	}

	if (x1 > 255)
	{
		s = s + 4;
		x1 = x1 >> 8;
	}

	if (x1 > 15)
	{
		s = s + 2;
		x1 = x1 >> 4;
	}

	if (x1 > 3)
	{
		s = s + 1;
	}

	g0 = 1 << s;
	g1 = (g0 + (x >> s)) >> 1;

	while (g1 < g0)
	{
		g0 = g1;
		g1 = (g0 + (x / g0)) >> 1;
	}

	return g0;
}

int32_t icbrt(uint32_t x)
{
	int32_t s;
	uint32_t b;
	uint32_t y = 0;
	uint32_t y2 = 0;

	for (s = 30; s >= 0; s -= 3)
	{
		y2 = 4 * y2;
		y = 2 * y;
		b = (3 * (y2 + y) + 1) << s;

		if (x >= b)
		{
			x = x - b;
			y2 = y2 + (2 * y) + 1;
			y = y + 1;
		}
	}

	return y;
}

// POW

static const uint8_t ipow_lut[31] =
{
	 0, 1, 2, 2, 3, 3, 3, 3,
	 4, 4, 4, 4, 4, 4, 4, 4,
	 5, 5, 5, 5, 5, 5, 5, 5,
	 5, 5, 5, 5, 5, 5, 5,
};

// exp < 31
int32_t ipow(int32_t base, uint8_t exp)
{
	int32_t result = 1;

	if (exp > 30)
	{
		return base;
	}

	// fallthrough
	switch (ipow_lut[exp])
	{
		case 5:
		{
			if (exp & 1)
			{
				result *= base;
			}

			exp >>= 1;
			base *= base;
		}
		case 4:
		{
			if (exp & 1)
			{
				result *= base;
			}

			exp >>= 1;
			base *= base;
		}
		case 3:
		{
			if (exp & 1)
			{
				result *= base;
			}

			exp >>= 1;
			base *= base;
		}
		case 2:
		{
			if (exp & 1)
			{
				result *= base;
			}

			exp >>= 1;
			base *= base;
		}
		case 1:
		{
			if (exp & 1)
			{
				result *= base;
			}
		}
		default:
		{
			return result;
		}
	}
}

uint32_t iatan2(int32_t x, int32_t y)
{
	uint8_t tempdegree;
	uint8_t octant = 0;
	uint8_t comp = 0;

	uint32_t degree;
	uint32_t ux;
	uint32_t uy;

	// prepare x
	if (x < 0)
	{
		octant |= 0x01;
		x = -x;
	}

	ux = x;

	// prepare y
	if (y < 0)
	{
		octant |= 0x02;
		y = -y;
	}

	uy = y;

	// atan2 approximation
	if (ux > uy)
	{
		if (ux != 0)
		{
			degree = (uy * 45) / ux;
		}
		else
		{
			degree = 90;
		}

		octant |= 0x04;
	}
	else
	{
		if (uy != 0)
		{
			degree = (ux * 45) / uy;
		}
		else
		{
			degree = 0;
		}
	}

	tempdegree = degree;

	if (tempdegree > 23)
	{
		if (tempdegree < 43)
		{
			comp++;
		}

		if (tempdegree < 41)
		{
			comp++;
		}

		if (tempdegree < 37)
		{
			comp++;
		}

		if (tempdegree < 35)
		{
			comp++;
		}

		if (tempdegree < 26)
		{
			comp++;
		}
	}
	else
	{
		if (tempdegree > 2)
		{
			comp++;
		}

		if (tempdegree > 6)
		{
			comp++;
		}

		if (tempdegree > 10)
		{
			comp++;
		}

		if (tempdegree > 13)
		{
			comp++;
		}
	}

	degree += comp;

	if (octant & 0x04)
	{
		degree = 90 - degree;
	}

	if (octant & 0x02)
	{
		if (octant & 0x01)
		{
			degree = 180 + degree;
		}
		else
		{
			degree = 180 - degree;
		}
	}
	else
	{
		if (octant & 0x01)
		{
			degree = (360 - degree);
		}
	}

	return degree;
}
