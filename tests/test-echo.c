#include "./tests.h"
#include "../minishell.h"

static int	run_echo_test(char **args, char *expected)
{
	int		saved_stdout;
	char		*actual;

	saved_stdout = start_capture();
	if (saved_stdout == -1)
		return (EXIT_FAILURE);
	ft_echo(args);
	actual = end_capture(saved_stdout);
	if (!actual)
		return (EXIT_FAILURE);
	if (expected == NULL)
	{
		if (actual == NULL || actual[0] == '\0')
		{
			free(actual);
			return (EXIT_SUCCESS);
		}
	}
	else if (ft_strncmp(actual, expected, ft_strlen(expected)) != 0 
		|| actual[ft_strlen(expected)] != '\0')
	{
		free(actual);
		return (EXIT_FAILURE);
	}
	free(actual);
	return (EXIT_SUCCESS);
}

int	should_print_single_argument(void)
{
	char		*args[] = {"echo", "hello", NULL};

	return (run_echo_test(args, "hello\n"));
}

int	should_print_multiple_arguments(void)
{
	char		*args[] = {"echo", "a", "b", "c", NULL};

	return (run_echo_test(args, "a b c\n"));
}

int	should_print_only_newline_when_no_args(void)
{
	char		*args[] = {"echo", NULL};

	return (run_echo_test(args, "\n"));
}

int	should_handle_empty_strings(void)
{
	char		*args[] = {"echo", "", "hello", NULL};

	return (run_echo_test(args, " hello\n"));
}

int	should_handle_minus_n_flag(void)
{
	char		*args[] = {"echo", "-n", "hello", NULL};

	return (run_echo_test(args, "hello"));
}

int	should_treat_minus_n_as_text_if_not_first(void)
{
	char		*args[] = {"echo", "hello", "-n", NULL};

	return (run_echo_test(args, "hello -n\n"));
}

int	should_handle_only_minus_n(void)
{
	char		*args[] = {"echo", "-n", NULL};

	return (run_echo_test(args, ""));
}

int	main(void)
{
	RUN_TEST(should_print_single_argument);
	RUN_TEST(should_print_multiple_arguments);
	RUN_TEST(should_print_only_newline_when_no_args);
	RUN_TEST(should_handle_empty_strings);
	RUN_TEST(should_handle_minus_n_flag);
	RUN_TEST(should_treat_minus_n_as_text_if_not_first);
	RUN_TEST(should_handle_only_minus_n);
	return (0);
}
