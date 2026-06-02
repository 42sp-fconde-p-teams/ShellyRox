/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 21:44:52 by csilva-s          #+#    #+#             */
/*   Updated: 2026/06/01 19:03:59 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_here_doc(t_redir *redir, t_shelly *shelly)
{
	int		fd;
	t_redir	*tmp;

	tmp = redir;
	fd = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			fd = open("/tmp/.shelly_heredoc",
					O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (fd == -1)
				return (-1);
			read_and_write_here_doc(fd, tmp, shelly);
		}
		tmp = tmp->next;
	}
	return (fd);
}

static char	*expand_heredoc_line(char *line, t_redir *redir, t_shelly *shelly)
{
	char	*expand;

	if (redir->quoted)
		return (line);
	expand = expand_variables(line, shelly, BOOL_FALSE);
	free(line);
	return (expand);
}

void	read_and_write_here_doc(int fd, t_redir *redir, t_shelly *shelly)
{
	char	*line;
	char	*limiter;

	ft_putstr_fd("> ", 2);
	line = get_next_line(0);
	limiter = ft_strjoin(redir->filename, "\n");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(redir->filename) + 2) == 0)
		{
			free(line);
			break ;
		}
		line = expand_heredoc_line(line, redir, shelly);
		ft_putstr_fd(line, fd);
		free(line);
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
	}
	free(limiter);
	close (fd);
}

void	set_here_doc_fd(void)
{
	int	fd;

	fd = open("/tmp/.shelly_heredoc", O_RDONLY);
	if (fd < 0)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	find_heredoc(t_ast_node *ast, t_shelly *shelly)
{
	int	heredoc;

	if (!ast)
		return ;
	if (ast->node_type == TOKEN_PIPE)
	{
		find_heredoc(ast->value.pipe->left, shelly);
		find_heredoc(ast->value.pipe->right, shelly);
	}
	else
	{
		if (ast->value.cmd)
		{
			heredoc = check_here_doc(ast->value.cmd->redir, shelly);
			if (heredoc == -1)
				return ;
		}
	}
}
