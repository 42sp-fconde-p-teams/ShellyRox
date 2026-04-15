#include "./tests.h"
#include "../minishell.h"

static char	*capture_export_output(char **args, t_shelly shell)
{
	static char	buf[2048];
	int			fd;
	int			saved_stdout;
	ssize_t		n;

	fd = open("/tmp/.test_export_out", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (NULL);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_export(args, &shell);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open("/tmp/.test_export_out", O_RDONLY);
	if (fd == -1)
		return (NULL);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_export_out");
	if (n <= 0)
		return (NULL);
	buf[n] = '\0';
	return (buf);
}

int	should_list_env_alphabetically(void)
{
	t_shelly	shell = {0};
	char	*envp[] = {"Z_VAR=last", "A_VAR=first", "M_VAR=middle", NULL};
	char	*args[] = {"export", NULL};
	char	*out;

	init_env_list(&shell, envp);
	out = capture_export_output(args, shell);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "A_VAR=first\nM_VAR=middle\nZ_VAR=last\n", 36) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_set_variable_with_value(void)
{
	t_shelly	shell = {0};
	char	*args[] = {"export", "TEST_VAR=123", NULL};
	char	*val;

	ft_export(args, &shell);
	val = get_env_value("TEST_VAR", &shell);
	if (!val || ft_strncmp(val, "123", 3) != 0)
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	should_set_variable_empty(void)
{
	t_shelly	shell = {0};
	char	*args[] = {"export", "TEST_VAR", NULL};
	char	*val;

	ft_export(args, &shell);
	val = get_env_value("TEST_VAR", &shell);
	if (!val || val[0] != '\0')
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	should_update_existing_variable(void)
{
	t_shelly	shell = {0};
	char	*args1[] = {"export", "TEST_VAR=VAL1", NULL};
	char	*args2[] = {"export", "TEST_VAR=VAL2", NULL};
	char	*val;

	ft_export(args1, &shell);
	ft_export(args2, &shell);
	val = get_env_value("TEST_VAR", &shell);
	if (!val || ft_strncmp(val, "VAL2", 4) != 0)
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	should_handle_multiple_args(void)
{
	t_shelly	shell = {0};
	char	*args[] = {"export", "A=1", "B=2", "C=3", NULL};
	char	*val;

	ft_export(args, &shell);
	val = get_env_value("A", &shell);
	if (!val || val[0] != '1')
		return (EXIT_FAILURE);
	free(val);
	val = get_env_value("B", &shell);
	if (!val || val[0] != '2')
		return (EXIT_FAILURE);
	free(val);
	val = get_env_value("C", &shell);
	if (!val || val[0] != '3')
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	should_reject_invalid_identifier_numeric(void)
{
	t_shelly	shell = {0};
	char	*args[] = {"export", "1VAR=VAL", NULL};
	char	*val;

	ft_export(args, &shell);
	val = get_env_value("1VAR", &shell);
	if (val != NULL)
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	should_reject_invalid_identifier_special(void)
{
	t_shelly	shell = {0};
	char	*args[] = {"export", "VAR-1=VAL", NULL};
	char	*val;

	ft_export(args, &shell);
	val = get_env_value("VAR-1", &shell);
	if (val != NULL)
		return (EXIT_FAILURE);
	free(val);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_list_env_alphabetically);
	RUN_TEST(should_set_variable_with_value);
	RUN_TEST(should_set_variable_empty);
	RUN_TEST(should_update_existing_variable);
	RUN_TEST(should_handle_multiple_args);
	RUN_TEST(should_reject_invalid_identifier_numeric);
	RUN_TEST(should_reject_invalid_identifier_special);
	return (0);
}
