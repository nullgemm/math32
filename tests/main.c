#include "testoasterror.h"

// source include
#include "tests.c"

#define COUNT_RESULTS 100
#define COUNT_FUNCS 9

int main()
{
	bool results[COUNT_RESULTS];

	void (*funcs[COUNT_FUNCS])(struct testoasterror*) =
	{
		test_zeros,
		test_ilog10,
		test_ilog2,
		test_isqrt,
		test_icbrt,
		test_ipow,
		test_iatan2,
		test_isin,
		test_icos,
	};

	struct testoasterror test;
	testoasterror_init(&test, results, COUNT_RESULTS, funcs, COUNT_FUNCS);
	testoasterror_run(&test);

	return 0;
}
