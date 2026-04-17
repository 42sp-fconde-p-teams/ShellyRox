/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_stdout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 23:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tests.h"

#define CAPTURE_FILE "/tmp/.minishell_test_capture"

int	start_capture(void)
{
	int	fd;
	int	saved_stdout;

	fd = open(CAPTURE_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(fd);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		close(saved_stdout);
		return (-1);
	}
	close(fd);
	return (saved_stdout);
}

char	*end_capture(int saved_stdout)
{
	char	*buf;
	int		fd;
	ssize_t	n;

	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	fd = open(CAPTURE_FILE, O_RDONLY);
	if (fd == -1)
		return (NULL);
	n = lseek(fd, 0, SEEK_END);
	if (n == -1)
	{
		close(fd);
		return (NULL);
	}
	buf = malloc(n + 1);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	lseek(fd, 0, SEEK_SET);
	if (read(fd, buf, n) != n)
	{
		free(buf);
		close(fd);
		return (NULL);
	}
	buf[n] = '\0';
	close(fd);
	unlink(CAPTURE_FILE);
	return (buf);
}
