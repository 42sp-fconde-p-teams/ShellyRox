#include "./tests.h"
#include <sys/wait.h>
#include <fcntl.h>

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
	node->value.cmd = cmd;
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

static void	add_test_redir(t_ast_node *node, t_token_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;
	if (!node->value.cmd)
		return ;
	node->value.cmd->redir = redir;
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
	if (ft_strchr(out, '\n') != NULL)
	{
		printf("\n\nTEST ===> Expected no newline, but found one in: '%s'\n\n", out);
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

int	should_create_empty_file_on_pipe_with_empty_redir(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "hello", NULL};
	t_ast_node	*left = make_cmd_node(args_l);
	t_ast_node	*right = make_cmd_node(NULL);
	char		*filename = "test_pipe_empty.txt";
	int			fd;

	init_env_list(&shell, environ);
	add_test_redir(right, TOKEN_REDIR_OUT, filename);
	executor(make_pipe_node(left, right), &shell);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (lseek(fd, 0, SEEK_END) != 0)
	{
		close(fd);
		unlink(filename);
		return (EXIT_FAILURE);
	}
	close(fd);
	unlink(filename);
	return (EXIT_SUCCESS);
}

int	should_write_to_file_on_pipe_with_cmd_and_redir(void)
{
	t_shelly	shell = {0};
	char		*args_l[] = {"echo", "hello", NULL};
	char		*args_r[] = {"cat", NULL};
	t_ast_node	*left = make_cmd_node(args_l);
	t_ast_node	*right = make_cmd_node(args_r);
	char		*filename = "test_pipe_content.txt";
	char		buf[16];
	int			fd;
	ssize_t		n;

	init_env_list(&shell, environ);
	add_test_redir(right, TOKEN_REDIR_OUT, filename);
	executor(make_pipe_node(left, right), &shell);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink(filename);
	if (n <= 0)
		return (EXIT_FAILURE);
	buf[n] = '\0';
	if (ft_strncmp(buf, "hello\n", 6) != 0)
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
	RUN_TEST(should_create_empty_file_on_pipe_with_empty_redir);
	RUN_TEST(should_write_to_file_on_pipe_with_cmd_and_redir);
	return (0);
}
