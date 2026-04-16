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

static char	*capture_output(t_ast_node *ast, t_shelly shell)
{
	static char	buf[1024];
	int			fd;
	int			saved_stdout;
	ssize_t		n;

	fd = open("/tmp/.test_pipe_out", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (NULL);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	executor(ast, shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open("/tmp/.test_pipe_out", O_RDONLY);
	if (fd == -1)
		return (NULL);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_pipe_out");
	if (n <= 0)
		return (NULL);
	buf[n] = '\0';
	return (buf);
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

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	out = capture_output(
			make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)),
			shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
		return (EXIT_FAILURE);
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

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	inner_pipe = make_pipe_node(make_cmd_node(a_cat1), make_cmd_node(a_cat2));
	out = capture_output(
			make_pipe_node(make_cmd_node(a_echo), inner_pipe),
			shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
		return (EXIT_FAILURE);
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

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	out = capture_output(
			make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)),
			shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello\n", 6) != 0)
		return (EXIT_FAILURE);
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

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	out = capture_output(
			make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)),
			shell);
	if (out != NULL)
		return (EXIT_FAILURE);
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

	init_env_list(&shell, environ);
	shell.last_exit_status = 0;
	shell.suppress_output = BOOL_FALSE;
	out = capture_output(
			make_pipe_node(make_cmd_node(args_l), make_cmd_node(args_r)),
			shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "hello", 6) != 0)
		return (EXIT_FAILURE);
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
