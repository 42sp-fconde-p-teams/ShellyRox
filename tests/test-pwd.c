#include "./tests.h"
#include "../minishell.h"

static char	*capture_pwd_output(void)
{
	static char	buf[1024];
	int			fd;
	int			saved_stdout;
	ssize_t		n;

	fd = open("/tmp/.test_pwd_out", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (NULL);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_pwd();
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open("/tmp/.test_pwd_out", O_RDONLY);
	if (fd == -1)
		return (NULL);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_pwd_out");
	if (n <= 0)
		return (NULL);
	buf[n] = '\0';
	return (buf);
}

int	should_print_current_working_directory(void)
{
	char	*expected;
	char	*actual;

	expected = getcwd(NULL, 0);
	actual = capture_pwd_output();
	if (!expected || !actual)
		return (EXIT_FAILURE);
	if (ft_strncmp(actual, expected, ft_strlen(expected)) != 0)
	{
		free(expected);
		free(actual);
		return (EXIT_FAILURE);
	}
	free(expected);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_print_current_working_directory);
	return (0);
}
