/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 21:44:52 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/16 01:16:39 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_here_doc(t_redir *redir)
{
	int	fd;
	t_redir	*tmp;

	tmp = redir;
	fd = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			fd = open("/tmp/.shelly_heredoc", O_WRONLY | O_CREAT | O_TRUNC , 0600);
			if (fd == -1)
				return (-1);
			read_and_write_here_doc(fd, tmp);
		}
		tmp = tmp->next;
	}
	return (fd);
}

void	read_and_write_here_doc(int fd, t_redir *redir)
{
	char *line;

	ft_putstr_fd("> ", 0);
	while ((line = get_next_line(0)))
	{
		if (ft_strncmp(line, ft_strjoin(redir->filename, "\n\0"),
			ft_strlen(redir->filename) + 2) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("> ", 0);
	}
	close (fd);
}

void	set_here_doc_fd(void)
{
	int fd;

	fd = open("/tmp/.shelly_heredoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
