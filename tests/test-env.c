#include "./tests.h"
#include "../minishell.h"

static char	*capture_env_output(t_shelly shell)
{
	static char	buf[1024];
	int			fd;
	int			saved_stdout;
	ssize_t		n;

	fd = open("/tmp/.test_env_out", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (NULL);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_env(&shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open("/tmp/.test_env_out", O_RDONLY);
	if (fd == -1)
		return (NULL);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_env_out");
	if (n <= 0)
		return (NULL);
	buf[n] = '\0';
	return (buf);
}

int	should_print_provided_envp(void)
{
	t_shelly	shell = {0};
	char	*envp[] = {"VAR1=VAL1", "VAR2=VAL2", NULL};
	char	*out;

	init_env_list(&shell, envp);
	out = capture_env_output(shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "VAR1=VAL1\nVAR2=VAL2\n", 20) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_handle_null_envp(void)
{
	t_shelly	shell = {0};
	char	*out;

	out = capture_env_output(shell);
	if (out != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_handle_empty_envp(void)
{
	t_shelly	shell = {0};
	char	*envp[] = {NULL};
	char	*out;

	init_env_list(&shell, envp);
	out = capture_env_output(shell);
	if (out != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_print_provided_envp);
	RUN_TEST(should_handle_null_envp);
	RUN_TEST(should_handle_empty_envp);
	return (0);
}
