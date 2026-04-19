#include "./tests.h"
#include "../minishell.h"

int	should_print_provided_envp(void)
{
	t_shelly	shell = {0};
	char	*envp[] = {"VAR1=VAL1", "VAR2=VAL2", NULL};
	char	*out;
	int		saved_stdout;

	init_env_list(&shell, envp);
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	ft_env(&shell);
	out = end_capture(saved_stdout);
	if (!out)
		return (EXIT_FAILURE);
	if (ft_strncmp(out, "VAR1=VAL1\nVAR2=VAL2\n", 20) != 0)
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

int	should_handle_null_envp(void)
{
	t_shelly	shell = {0};
	char	*out;
	int		saved_stdout;

	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	ft_env(&shell);
	out = end_capture(saved_stdout);
	if (!out || out[0] != '\0')
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

int	should_handle_empty_envp(void)
{
	t_shelly	shell = {0};
	char	*envp[] = {NULL};
	char	*out;
	int		saved_stdout;

	init_env_list(&shell, envp);
	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	ft_env(&shell);
	out = end_capture(saved_stdout);
	if (!out || out[0] != '\0')
	{
		free(out);
		return (EXIT_FAILURE);
	}
	free(out);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_print_provided_envp);
	RUN_TEST(should_handle_null_envp);
	RUN_TEST(should_handle_empty_envp);
	return (0);
}
