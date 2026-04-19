#include "./tests.h"
#include "../minishell.h"

int	should_print_current_working_directory(void)
{
	char	*expected;
	char	*actual;
	int		saved_stdout;

	expected = getcwd(NULL, 0);
	saved_stdout = start_capture();
	if (saved_stdout == -1)
	{
		free(expected);
		return (EXIT_FAILURE);
	}
	ft_pwd();
	actual = end_capture(saved_stdout);
	if (!expected || !actual)
	{
		free(expected);
		free(actual);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(actual, expected, ft_strlen(expected)) != 0)
	{
		free(expected);
		free(actual);
		return (EXIT_FAILURE);
	}
	free(expected);
	free(actual);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_print_current_working_directory);
	return (0);
}
