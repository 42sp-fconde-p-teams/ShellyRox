
#include "../minishell.h"

#include <stdio.h>
#include <stdlib.h>

#define RUN_TEST(test_func) \
    if (test_func() != 0) { \
        fprintf(stderr, "      [FAIL] Case: %s\n", #test_func); \
        return 1; \
    } else { \
        printf("      [PASS] Case: %s\n", #test_func); \
    }

// dumb sample file
int	should_fail(void)
{
	ft_printf("PIZZA TIME!\n");
	if (ft_sample_fail() == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_fail);
	return (0);
}
