#include "../minishell.h"
#include "./tests.h"

int	shoud_fail_for_pipe_only_prompt(void)
{
	t_token tokens = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};

	if (input_checker(&tokens) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_pipe_at_start(void)
{
	t_token t1 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};
	t_token t2 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_pipe_at_end(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_consecutive_pipes(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};
	t_token t3 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};
	t_token t4 = {"grep", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	t2.next = &t3;
	t3.prev = &t2;
	t3.next = &t4;
	t4.prev = &t3;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_pass_for_valid_pipe(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};
	t_token t3 = {"grep", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	t2.next = &t3;
	t3.prev = &t2;
	if (input_checker(&t1) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_redir_at_end(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {">", TOKEN_REDIR_OUT, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_redir_before_pipe(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {">", TOKEN_REDIR_OUT, BOOL_FALSE, NULL, NULL};
	t_token t3 = {"|", TOKEN_PIPE, BOOL_FALSE, NULL, NULL};
	t_token t4 = {"grep", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	t2.next = &t3;
	t3.prev = &t2;
	t3.next = &t4;
	t4.prev = &t3;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_fail_for_consecutive_redirs(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {">", TOKEN_REDIR_OUT, BOOL_FALSE, NULL, NULL};
	t_token t3 = {"<", TOKEN_REDIR_IN, BOOL_FALSE, NULL, NULL};
	t_token t4 = {"file", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	t2.next = &t3;
	t3.prev = &t2;
	t3.next = &t4;
	t4.prev = &t3;
	if (input_checker(&t1) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	should_pass_for_valid_redir(void)
{
	t_token t1 = {"ls", TOKEN_WORD, BOOL_FALSE, NULL, NULL};
	t_token t2 = {">", TOKEN_REDIR_OUT, BOOL_FALSE, NULL, NULL};
	t_token t3 = {"out.txt", TOKEN_WORD, BOOL_FALSE, NULL, NULL};

	t1.next = &t2;
	t2.prev = &t1;
	t2.next = &t3;
	t3.prev = &t2;
	if (input_checker(&t1) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(shoud_fail_for_pipe_only_prompt);
	RUN_TEST(should_fail_for_pipe_at_start);
	RUN_TEST(should_fail_for_pipe_at_end);
	RUN_TEST(should_fail_for_consecutive_pipes);
	RUN_TEST(should_pass_for_valid_pipe);
	RUN_TEST(should_fail_for_redir_at_end);
	RUN_TEST(should_fail_for_redir_before_pipe);
	RUN_TEST(should_fail_for_consecutive_redirs);
	RUN_TEST(should_pass_for_valid_redir);
	return (0);
}
