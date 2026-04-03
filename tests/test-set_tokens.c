
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
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
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
	else if (token->next != NULL)
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
	else if (token->prev == NULL && token->next == NULL)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	should_tokenize_empty_string_between_double_quotes_as_token_word(void)
{
	char	str_in[] = "echo \"\" test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	printf("\ntoken value: %s\n", token->next->value);
	printf("\ntoken type: %d\n", token->next->type);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\"\"", 1) == EXIT_SUCCESS
		&& token->next->type == TOKEN_WORD
		&& ft_strncmp(token->next->next->value, "test", 4) == EXIT_SUCCESS)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	should_tokenize_empty_string_between_simple_quotes_as_token_word(void)
{
	char	str_in[] = "echo \'\' test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	printf("\ntoken value: %s\n", token->next->value);
	printf("\ntoken type: %d\n", token->next->type);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\'\'", 1) == EXIT_SUCCESS
		&& token->next->type == TOKEN_WORD
		&& ft_strncmp(token->next->next->value, "test", 4) == EXIT_SUCCESS)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}
// WIP
int	should_create_list_with_quotes_combination(void)
{
	char	str_in[] = "echo 'mixed\"quotes'and\"more\"";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, "echo", 4) == EXIT_SUCCESS
		&& ft_strncmp(token->next->value, "\'mixed\"quotes\'", 14) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->value, "and", 3) == EXIT_SUCCESS
		&& ft_strncmp(token->next->next->next->value, "\"more\"", 6) == EXIT_SUCCESS
		&& token->next->next->next->next == NULL)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_correctly_list_for_input_with_pipe_and_no_space(void)
{
	char	str_in[] = "echo test|wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->next->next->value, "|", 1) == EXIT_SUCCESS
		&& token->next->next->type == TOKEN_PIPE)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_correctly_list_for_input_with_redirect_in_and_no_space(void)
{
	char	str_in[] = "echo test<wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->next->next->value, "<", 1) == EXIT_SUCCESS
		&& token->next->next->type == TOKEN_REDIR_IN)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_correctly_list_for_input_with_redirect_out_and_no_space(void)
{
	char	str_in[] = "echo test>wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->next->next->value, ">", 1) == EXIT_SUCCESS
		&& token->next->next->type == TOKEN_REDIR_OUT)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_correctly_list_for_input_with_append_and_no_space(void)
{
	char	str_in[] = "echo test>>wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->next->next->value, ">>", 2) == EXIT_SUCCESS
		&& token->next->next->type == TOKEN_APPEND)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_correctly_list_for_input_with_heredoc_and_no_space(void)
{
	char	str_in[] = "echo test<<wc -l";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->next->next->value, "<<", 2) == EXIT_SUCCESS
		&& token->next->next->type == TOKEN_HEREDOC)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
		return (EXIT_FAILURE);
	}
}

int	set_third_node_as_word(void)
{
	char	str_in[] = "command >> size -test";
	t_token	*token = NULL;

	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (token->next->next->type == TOKEN_WORD)
	{
		clear_token_list(&token);
		return (EXIT_SUCCESS);
	}
	else
	{
		clear_token_list(&token);
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
	RUN_TEST(should_create_list_with_quotes_combination);
	RUN_TEST(should_tokenize_empty_string_between_double_quotes_as_token_word);
	RUN_TEST(should_tokenize_empty_string_between_simple_quotes_as_token_word);
	RUN_TEST(set_correctly_reverse_link_for_list_of_three);
	RUN_TEST(set_correctly_list_for_input_with_pipe_and_no_space);
	RUN_TEST(set_correctly_list_for_input_with_redirect_in_and_no_space);
	RUN_TEST(set_correctly_list_for_input_with_redirect_out_and_no_space);
	RUN_TEST(set_correctly_list_for_input_with_append_and_no_space);
	RUN_TEST(set_correctly_list_for_input_with_heredoc_and_no_space);

	// token type tests
	RUN_TEST(set_second_node_as_pipe);
	RUN_TEST(set_second_node_as_redirect_in);
	RUN_TEST(set_second_node_as_redirect_out);
	RUN_TEST(set_second_node_as_heredoc);
	RUN_TEST(set_second_node_as_append);
	RUN_TEST(set_third_node_as_word);

	return (0);
}
