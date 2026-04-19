#include "../minishell.h"
#include "./tests.h"

int	first_token_must_be_lenght_5(void)
{
	char	str[] = "token size test.";
	if (get_token_len(str) == 5)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	first_token_between_simple_quotes_must_be_lenght_12(void)
{
	char	str[] = "'token size' test.";
	if (get_token_len(str) == 12)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	first_token_between_double_quotes_must_be_lenght_12(void)
{
	char	str[] = "\"token size\" test.";
	if (get_token_len(str) == 12)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(first_token_must_be_lenght_5);
	RUN_TEST(first_token_between_simple_quotes_must_be_lenght_12);
	RUN_TEST(first_token_between_double_quotes_must_be_lenght_12);
	return (0);
}
