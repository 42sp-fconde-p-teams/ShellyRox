#include "../minishell.h"
#include "./tests.h"

int	shoud_fail_for_pipe_only_prompt(void)
{

	t_token tokens;

	tokens.value = "|";
	tokens.next = NULL;
	tokens.prev = NULL;
	tokens.type = TOKEN_PIPE;
	if (input_checker((&tokens)) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(shoud_fail_for_pipe_only_prompt);
	return (0);
}
