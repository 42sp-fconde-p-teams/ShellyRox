#include "../minishell.h"
#include "./tests.h"

int	should_expand_tilde_to_home(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"HOME=/home/dot", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("~");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "/home/dot", 9) == 0)
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

int	should_not_expand_tilde_if_no_home_set(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("~");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "~", 1) == 0)
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

int	should_expand_variable(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"VAR=hello", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("$VAR");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "hello", 5) == 0)
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

int	should_expand_exit_status(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 42;
	token = set_tokens("$?");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "42", 2) == 0)
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

int	should_remove_double_quotes(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("\"hello\"");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "hello", 5) == 0)
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

int	should_remove_single_quotes(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("'hello'");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "hello", 5) == 0)
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

int	should_not_expand_in_single_quotes(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"VAR=hello", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	// When set_tokens parses '$VAR', it sees it as a word but with quotes.
	// Actually, set_tokens doesn't set 'quoted' flag yet properly.
	// Let's check set_tokens again.
	token = set_tokens("'$VAR'");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "$VAR", 4) == 0)
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

int	should_expand_in_double_quotes(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"VAR=hello", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("\"$VAR\"");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	if (ft_strncmp(token->value, "hello", 5) == 0)
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

int	should_split_words_if_not_quoted(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"VAR=hello world", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("$VAR");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	// Should have two tokens: "hello" and "world"
	if (ft_strncmp(token->value, "hello", 5) == 0 && \
		token->next != NULL && \
		ft_strncmp(token->next->value, "world", 5) == 0)
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

int	should_not_split_words_if_quoted(void)
{
	t_token	*token = NULL;
	t_shelly shelly;
	char *envp[] = {"VAR=hello world", NULL};

	shelly.envp = envp;
	shelly.last_exit_status = 0;
	token = set_tokens("\"$VAR\"");
	if (!token)
		return (EXIT_FAILURE);
	token = expander(token, &shelly);
	// Should have one token: "hello world"
	if (ft_strncmp(token->value, "hello world", 11) == 0 && \
		token->next == NULL)
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
	RUN_TEST(should_expand_tilde_to_home);
	RUN_TEST(should_not_expand_tilde_if_no_home_set);
	RUN_TEST(should_expand_variable);
	RUN_TEST(should_expand_exit_status);
	RUN_TEST(should_remove_double_quotes);
	RUN_TEST(should_remove_single_quotes);
	RUN_TEST(should_not_expand_in_single_quotes);
	RUN_TEST(should_expand_in_double_quotes);
	RUN_TEST(should_split_words_if_not_quoted);
	RUN_TEST(should_not_split_words_if_quoted);

	return (0);
}
