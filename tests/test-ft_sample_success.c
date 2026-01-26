
#include "../minishell.h"
#include "./tests.h"

// dumb sample file
int	should_pass02(void)
{
	// ft_printf("PIZZA TIME!\n");
	if (ft_sample_success() == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_pass02);
	return (0);
}