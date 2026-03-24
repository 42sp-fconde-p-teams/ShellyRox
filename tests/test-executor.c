#include "./tests.h"
#include <sys/wait.h>

extern char **environ;

static t_ast_node	*make_cmd_node(char **args)
{
	t_ast_node	*node;
	t_command	*cmd;

	node = malloc(sizeof(t_ast_node));
	cmd  = malloc(sizeof(t_command));
	cmd->cmd   = args;
	cmd->redir = NULL;
	node->node_type    = TOKEN_WORD;
	node->value.command = cmd;
	return (node);
}

int	should_find_path_from_envp(void)
{
	char	*envp[] = {"PATH=/usr/bin:/bin", NULL};
	char	**paths;

	paths = find_path(envp);
	if (!paths || !paths[0])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_find_path_when_not_first_entry(void)
{
	char	*envp[] = {"HOME=/home/user", "PATH=/usr/bin:/bin", NULL};
	char	**paths;

	paths = find_path(envp);
	if (!paths || !paths[0])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_return_null_when_no_path_in_envp(void)
{
	char	*envp[] = {"HOME=/home/user", "USER=tester", NULL};
	char	**paths;

	paths = find_path(envp);
	if (paths != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_split_path_entries_correctly(void)
{
	char	*envp[] = {"PATH=/usr/bin:/bin", NULL};
	char	**paths;

	paths = find_path(envp);
	if (!paths || !paths[0] || !paths[1])
		return (EXIT_FAILURE);
	if (ft_strncmp(paths[0], "/usr/bin", 8) != 0)
		return (EXIT_FAILURE);
	if (ft_strncmp(paths[1], "/bin", 4) != 0)
		return (EXIT_FAILURE);
	if (paths[2] != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_resolve_command_from_path(void)
{
	char	*path[] = {"/usr/bin", "/bin", NULL};
	char	*result;

	result = find_command(path, "ls");
	if (!result)
		return (EXIT_FAILURE);
	if (access(result, F_OK | X_OK) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_return_null_for_unknown_command(void)
{
	char	*path[] = {"/usr/bin", "/bin", NULL};
	char	*result;

	result = find_command(path, "this_cmd_does_not_exist_xyz123");
	if (result != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_return_full_path_when_cmd_is_absolute(void)
{
	char	*path[] = {"/usr/bin", "/bin", NULL};
	char	*result;

	result = find_command(path, "/bin/ls");
	if (!result)
		return (EXIT_FAILURE);
	if (access(result, F_OK | X_OK) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_return_zero_on_successful_command(void)
{
	t_shelly	shell;
	t_ast_node	*node;
	char		*args[] = {"ls", NULL};
	int			status;

	shell.envp = environ;
	shell.last_exit_status = 0;
	node = make_cmd_node(args);
	status = executor(node, shell);
	return (WEXITSTATUS(status) == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int	should_return_nonzero_on_failed_command(void)
{
	t_shelly	shell;
	t_ast_node	*node;
	char		*args[] = {"ls", "/this/path/does/not/exist/xyz", NULL};
	int			status;

	shell.envp = environ;
	shell.last_exit_status = 0;
	node = make_cmd_node(args);
	status = executor(node, shell);
	return (WEXITSTATUS(status) != 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int	should_return_nonzero_for_missing_command(void)
{
	t_shelly	shell;
	t_ast_node	*node;
	char		*args[] = {"this_cmd_does_not_exist_xyz123", NULL};
	int			status;

	shell.envp = environ;
	shell.last_exit_status = 0;
	node = make_cmd_node(args);
	status = executor(node, shell);
	return (status != 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_find_path_from_envp);
	RUN_TEST(should_find_path_when_not_first_entry);
	RUN_TEST(should_return_null_when_no_path_in_envp);
	RUN_TEST(should_split_path_entries_correctly);
	RUN_TEST(should_resolve_command_from_path);
	RUN_TEST(should_return_null_for_unknown_command);
	RUN_TEST(should_return_full_path_when_cmd_is_absolute);
	RUN_TEST(should_return_zero_on_successful_command);
	RUN_TEST(should_return_nonzero_on_failed_command);
	RUN_TEST(should_return_nonzero_for_missing_command);
	return (0);
}
