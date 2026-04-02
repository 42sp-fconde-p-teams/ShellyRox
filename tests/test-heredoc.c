#include "./tests.h"

static t_redir	*make_redir(t_token_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->filename = filename;
	redir->next = NULL;
	return (redir);
}

static void	pipe_stdin(const char *content, int *saved_stdin)
{
	int	pipefd[2];

	pipe(pipefd);
	*saved_stdin = dup(STDIN_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
}

static void	restore_stdin(int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	should_return_no_error_when_redir_is_null(void)
{
	int	result;

	result = check_here_doc(NULL);
	return (result != -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int	should_return_no_error_with_non_heredoc_redir(void)
{
	t_redir	*redir;
	int		result;

	redir = make_redir(TOKEN_REDIR_OUT, "out.txt");
	result = check_here_doc(redir);
	free(redir);
	return (result != -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}

int	should_write_content_up_to_delimiter(void)
{
	t_redir	redir;
	int		saved_stdin;
	int		fd;
	char	buf[64];
	ssize_t	n;

	redir.type = TOKEN_HEREDOC;
	redir.filename = "EOF";
	redir.next = NULL;
	pipe_stdin("hello\nworld\nEOF\n", &saved_stdin);
	fd = open("/tmp/.test_heredoc_write", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		restore_stdin(saved_stdin);
		return (EXIT_FAILURE);
	}
	read_and_write_here_doc(fd, &redir);
	restore_stdin(saved_stdin);
	fd = open("/tmp/.test_heredoc_write", O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_heredoc_write");
	if (n <= 0)
		return (EXIT_FAILURE);
	buf[n] = '\0';
	if (ft_strncmp(buf, "hello\nworld\n", 12) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_not_write_delimiter_line(void)
{
	t_redir	redir;
	int		saved_stdin;
	int		fd;
	char	buf[64];
	ssize_t	n;

	redir.type = TOKEN_HEREDOC;
	redir.filename = "STOP";
	redir.next = NULL;
	pipe_stdin("line\nSTOP\nextra\n", &saved_stdin);
	fd = open("/tmp/.test_heredoc_delim", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		restore_stdin(saved_stdin);
		return (EXIT_FAILURE);
	}
	read_and_write_here_doc(fd, &redir);
	restore_stdin(saved_stdin);
	fd = open("/tmp/.test_heredoc_delim", O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	unlink("/tmp/.test_heredoc_delim");
	buf[n] = '\0';
	if (ft_strnstr(buf, "STOP", n) != NULL)
		return (EXIT_FAILURE);
	if (ft_strnstr(buf, "extra", n) != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_redirect_heredoc_file_to_stdin(void)
{
	int		fd;
	int		saved_stdin;
	char	buf[32];
	ssize_t	n;

	fd = open("/tmp/.shelly_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (EXIT_FAILURE);
	write(fd, "from heredoc\n", 13);
	close(fd);
	saved_stdin = dup(STDIN_FILENO);
	set_here_doc_fd();
	n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	restore_stdin(saved_stdin);
	unlink("/tmp/.shelly_heredoc");
	if (n <= 0)
		return (EXIT_FAILURE);
	buf[n] = '\0';
	if (ft_strncmp(buf, "from heredoc\n", 13) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_create_temp_file_when_heredoc_found(void)
{
	t_redir	*redir;
	int		saved_stdin;
	int		result;

	redir = make_redir(TOKEN_HEREDOC, "EOF");
	pipe_stdin("content\nEOF\n", &saved_stdin);
	result = check_here_doc(redir);
	restore_stdin(saved_stdin);
	free(redir);
	if (result == -1)
		return (EXIT_FAILURE);
	if (access("/tmp/.shelly_heredoc", F_OK) != 0)
		return (EXIT_FAILURE);
	unlink("/tmp/.shelly_heredoc");
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_return_no_error_when_redir_is_null);
	RUN_TEST(should_return_no_error_with_non_heredoc_redir);
	RUN_TEST(should_write_content_up_to_delimiter);
	RUN_TEST(should_not_write_delimiter_line);
	RUN_TEST(should_redirect_heredoc_file_to_stdin);
	RUN_TEST(should_create_temp_file_when_heredoc_found);
	return (0);
}
