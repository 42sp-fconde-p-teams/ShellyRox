#include "../minishell.h"
#include "./tests.h"

int	shoud_frees_all_token_nodes(void)
{
	char	str_in[] = "command >> size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	clear_token_list(&token);
	if (!token)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	// simple token creation tests
	RUN_TEST(shoud_frees_all_token_nodes);
}
