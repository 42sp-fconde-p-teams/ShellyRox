
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

int	return_null_for_empty_token(void)
{
	char	str_in[] = "";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_SUCCESS);
	else
	{
		free(token);
		return (EXIT_FAILURE);
	}
}

int	return_null_for_only_spaces_token(void)
{
	char	str_in[] = "    ";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_SUCCESS);
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

int	create_quoted_chunk_as_one_token(void)
{
	char	str_in[] = "echo \"token size\" test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\"token size\"", 12) == EXIT_SUCCESS
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

int	create_list_ignoring_spaces(void)
{
	char	str_in[] = "    token size   test     ";
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

int	create_list_with_input_containing_pipe_with_spaces(void)
{
	char	str_in[] = "echo \"lets go!\" | wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\"lets go!\"", 10) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->value, "|", 1) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->next->value, "wc", 2) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->next->next->value, "-l", 2) == EXIT_SUCCESS)
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

int	create_list_with_simple_quotes_between_double_quotes(void)
{
	char	str_in[] = "echo \"let's que let's!\" | wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\"let's que let's!\"", 18) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->value, "|", 1) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->next->value, "wc", 2) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->next->next->value, "-l", 2) == EXIT_SUCCESS)
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

int	set_second_node_as_pipe(void)
{
	char	str_in[] = "command | size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->type == TOKEN_PIPE)
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

int	set_second_node_as_redirect_in(void)
{
	char	str_in[] = "command < size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->type == TOKEN_REDIR_IN)
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

int	set_second_node_as_redirect_out(void)
{
	char	str_in[] = "command > size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->type == TOKEN_REDIR_OUT)
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

int	set_second_node_as_heredoc(void)
{
	char	str_in[] = "command << size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->type == TOKEN_HEREDOC)
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

int	set_second_node_as_append(void)
{
	char	str_in[] = "command >> size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->type == TOKEN_APPEND)
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
	RUN_TEST(return_null_for_empty_token);
	RUN_TEST(return_null_for_only_spaces_token);
	// token list tests
	RUN_TEST(create_list_with_three_tokens);
	RUN_TEST(create_quoted_chunk_as_one_token);
	RUN_TEST(create_list_ignoring_spaces);
	RUN_TEST(create_list_with_input_containing_pipe_with_spaces);
	RUN_TEST(create_list_with_simple_quotes_between_double_quotes);
	RUN_TEST(set_correctly_reverse_link_for_list_of_three);
	// token type tests
	RUN_TEST(set_second_node_as_pipe);
	RUN_TEST(set_second_node_as_redirect_in);
	RUN_TEST(set_second_node_as_redirect_out);
	RUN_TEST(set_second_node_as_heredoc);
	RUN_TEST(set_second_node_as_append);

	return (0);
}
