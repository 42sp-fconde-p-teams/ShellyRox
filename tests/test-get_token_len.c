
#include "../minishell.h"
#include "./tests.h"

int	first_token_must_be_lenght_6(void)
{
	int		i = 0;
	char	str[] = "token size test.";

	if (get_token_len(str) == 6)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(first_token_must_be_lenght_6);
	return (0);
}
