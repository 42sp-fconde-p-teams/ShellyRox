/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:59 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/30 22:18:25 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	redirect_in(t_redir *redir)
{
	int	fd;

	if ((fd = open(redir->filename, O_RDONLY)) < 0)
	{
		perror (redir->filename);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static	int	redirect_out(t_redir *redir)
{
	int	fd;

	if ((fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		perror (redir->filename);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static	int	redirect_append(t_redir *redir)
{
	int	fd;

	if ((fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
	{
		perror (redir->filename);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirections(t_redir *redir)
{
	int		status;
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_IN)
			status = redirect_in(tmp);
		else if (tmp->type == TOKEN_REDIR_OUT)
			status = redirect_out(tmp);
		else if (tmp->type == TOKEN_APPEND)
			status = redirect_append(tmp);
		else if (tmp->type == TOKEN_HEREDOC)
			status = 0;
		if (status != 0)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
