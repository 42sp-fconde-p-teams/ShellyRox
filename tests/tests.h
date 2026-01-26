
#ifndef TESTS_H
# define TESTS_H

# include "../lib/libft/libft.h"
# include "../minishell.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

// def funny stuff here, friendo!
#define RUN_TEST(test_func) \
	if (test_func() != 0) { \
		printf("      [FAIL] Case: %s\n", #test_func); \
	} else { \
		printf("      [PASS] Case: %s\n", #test_func); \
	}

#endif