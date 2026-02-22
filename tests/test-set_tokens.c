
#include "../minishell.h"
#include "./tests.h"

int	put_value_to_a_new_token_node(void)
{
	char	str_in[] = "teste";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, str_in, 6) == EXIT_SUCCESS)
	{
		free(token);
		return (EXIT_SUCCESS);
	}
	else
	{
		free(token);
		return (EXIT_FAILURE);
	}
}

int	create_new_node_with_null_prev_and_next(void)
{
	char	str_in[] = "teste";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->prev != NULL)
	{
		free(token);
		return (EXIT_FAILURE);
	}
	else if (token->next != NULL)
	{
		free(token);
		return (EXIT_FAILURE);
	}
	else if (token->prev == NULL && token->next == NULL)
	{
		free(token);
		return (EXIT_SUCCESS);
	}
	else
	{
		free(token);
		return (EXIT_FAILURE);
	}
}

int	main(void)
{
	// simple token creation tests
	RUN_TEST(put_value_to_a_new_token_node);
	RUN_TEST(create_new_node_with_null_prev_and_next);
	// token list tests
	return (0);
}
