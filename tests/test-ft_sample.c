
#include "../minishell.h"
#include "./tests.h"

// dumb sample file
int	should_pass01(void)
{
	// ft_printf("PIZZA TIME!\n");
	if (ft_sample() == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	should_fail_hard(void)
{
	// ft_printf("PIZZA TIME!\n");
	if (ft_sample() == 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_pass01);
	RUN_TEST(should_fail_hard);
	return (0);
}
