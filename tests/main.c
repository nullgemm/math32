#include "testoasterror.h"

// source include
#include "tests.c"

#define COUNT_RESULTS 100
#define COUNT_FUNCS 1

int main()
{
	bool results[COUNT_RESULTS];

	void (*funcs[COUNT_FUNCS])(struct testoasterror*) =
	{
		test_zeros,
	};

	struct testoasterror test;
	testoasterror_init(&test, results, COUNT_RESULTS, funcs, COUNT_FUNCS);
	testoasterror_run(&test);

	return 0;
}
