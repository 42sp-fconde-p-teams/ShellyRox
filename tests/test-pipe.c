#include "./tests.h"
#include <sys/wait.h>

extern char **environ;

static t_ast_node	*make_cmd_node(char **args)
{
	t_ast_node	*node;
	t_command	*cmd;

	node = malloc(sizeof(t_ast_node));
	cmd = malloc(sizeof(t_command));
	cmd->cmd = args;
	cmd->redir = NULL;
	node->node_type = TOKEN_WORD;
	node->value.command = cmd;
	return (node);
}

static t_ast_node	*make_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;
	t_pipe		*p;

	node = malloc(sizeof(t_ast_node));
	p = malloc(sizeof(t_pipe));
	p->left = left;
	p->right = right;
	node->node_type = TOKEN_PIPE;
	node->value.pipe = p;
	return (node);
}

/*
** echo hello | cat → "hello\n"
*/
int	should_pipe_echo_to_cat(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "hello", NULL};
	char		*args_r[] = {"cat", NULL};
	char		*out;
	int			saved_stdout;

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	executor(make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)), &shell);
	out = end_capture(saved_stdout);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

/*
** echo hello | cat | cat → "hello\n"
*/
int	should_chain_three_commands(void)
{
	t_shelly	shell = {0};
	char		*a_echo[] = {"echo", "hello", NULL};
	char		*a_cat1[] = {"cat", NULL};
	char		*a_cat2[] = {"cat", NULL};
	t_ast_node	*inner_pipe;
	char		*out;
	int			saved_stdout;

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	inner_pipe = make_pipe_node(make_cmd_node(a_cat1), make_cmd_node(a_cat2));
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	executor(make_pipe_node(make_cmd_node(a_echo), inner_pipe), &shell);
	out = end_capture(saved_stdout);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

/*
** echo hello | grep hello → "hello\n"
*/
int	should_pipe_echo_to_grep_match(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "hello", NULL};
	char		*args_r[] = {"grep", "hello", NULL};
	char		*out;
	int			saved_stdout;

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	executor(make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)), &shell);
	out = end_capture(saved_stdout);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

/*
** echo hello | grep nope → sem output
*/
int	should_pipe_grep_no_match_produces_no_output(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "hello", NULL};
	char		*args_r[] = {"grep", "nope", NULL};
	char		*out;
	int			saved_stdout;

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	executor(make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)), &shell);
	out = end_capture(saved_stdout);
	if (!out || out[0] != '\0')
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

/*
** echo -n hello | cat → "hello" (sem newline)
*/
int	should_pipe_echo_n_no_newline(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "-n", "hello", NULL};
	char		*args_r[] = {"cat", NULL};
	char		*out;
	int			saved_stdout;

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	executor(make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)), &shell);
	out = end_capture(saved_stdout);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello", 6) != 0)
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_pipe_echo_to_cat);
	RUN_TEST(should_chain_three_commands);
	RUN_TEST(should_pipe_echo_to_grep_match);
	RUN_TEST(should_pipe_grep_no_match_produces_no_output);
	RUN_TEST(should_pipe_echo_n_no_newline);
	return (0);
}
