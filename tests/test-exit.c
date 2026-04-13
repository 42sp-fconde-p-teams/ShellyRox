#include "./tests.h"
#include "../minishell.h"

static int	run_exit_test(char **args, int expected_status, int initial_last_status)
{
	t_shelly	shell = {0};
	pid_t		pid;
	int			status;

	shell.last_exit_status = initial_last_status;
	pid = fork();
	if (pid == 0)
	{
		ft_exit(&shell, args);
		exit((expected_status + 1) & 255); // Fallback: must differ from expected_status
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == expected_status)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	should_exit_with_last_status_when_no_args(void)
{
	char	*args[] = {"exit", NULL};

	return (run_exit_test(args, 42, 42));
}

int	should_exit_with_zero_when_arg_is_0(void)
{
	char	*args[] = {"exit", "0", NULL};

	return (run_exit_test(args, 0, 0));
}

int	should_exit_with_provided_value(void)
{
	char	*args[] = {"exit", "42", NULL};

	return (run_exit_test(args, 42, 0));
}

int	should_exit_with_truncated_value(void)
{
	// 257 & 255 = 1
	char	*args[] = {"exit", "257", NULL};

	return (run_exit_test(args, 1, 0));
}

int	should_exit_with_255_on_non_numeric_arg(void)
{
	char	*args[] = {"exit", "abc", NULL};

	return (run_exit_test(args, 255, 0));
}

int	should_exit_with_255_on_too_many_args(void)
{
	char	*args[] = {"exit", "1", "2", NULL};

	return (run_exit_test(args, 255, 0));
}

int	main(void)
{
	RUN_TEST(should_exit_with_last_status_when_no_args);
	RUN_TEST(should_exit_with_zero_when_arg_is_0);
	RUN_TEST(should_exit_with_provided_value);
	RUN_TEST(should_exit_with_truncated_value);
	RUN_TEST(should_exit_with_255_on_non_numeric_arg);
	RUN_TEST(should_exit_with_255_on_too_many_args);
	return (0);
}
