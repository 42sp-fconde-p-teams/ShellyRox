
#ifndef TESTS_H
# define TESTS_H

// project header files
# include "../lib/libft/libft.h"
# include "../minishell.h"

// other header files
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

// def funny stuff here, friendo!

// MACRO for individual test running and result printing
#define RUN_TEST(test_func) \
	if (test_func() != 0) { \
		printf("      [FAIL] Case: %s\n", #test_func); \
	} else { \
		printf("      [PASS] Case: %s\n", #test_func); \
	}

#endif