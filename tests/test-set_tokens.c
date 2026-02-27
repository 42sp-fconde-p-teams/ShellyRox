
#include "../minishell.h"
#include "./tests.h"

int	put_value_to_a_new_token_node(void)
{
	char	str_in[] = "token size test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, str_in, 5) == EXIT_SUCCESS)
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
	char	str_in[] = "token";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
	{
		return (EXIT_FAILURE);
	}
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

int	create_list_with_three_tokens(void)
{
	char	str_in[] = "token size test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "token", 5) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "size", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->value, "test", 4) == EXIT_SUCCESS)
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

int	set_correctly_reverse_link_for_list_of_three(void)
{
	char	str_in[] = "token size test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	token = token->next->next;
	if (ft_strncmp(token->value, "test", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->prev->value, "size", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->prev->prev->value, "token", 5) == EXIT_SUCCESS)
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
	RUN_TEST(create_list_with_three_tokens);
	RUN_TEST(set_correctly_reverse_link_for_list_of_three);
	// token list tests
	return (0);
}
