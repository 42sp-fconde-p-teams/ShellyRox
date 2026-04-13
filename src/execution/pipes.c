/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:50 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/31 22:43:25 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pipe_command(t_ast_node *ast, t_shelly shelly)
{
	char	*cmd_line;
	int		here_doc;
	char	**paths;

	here_doc = check_here_doc(ast->value.command->redir);
	paths = find_path(&shelly);
	cmd_line = find_command(paths, ast->value.command->cmd[0]);
	if (paths)
		ft_free_array(paths);
	if (cmd_line == NULL || here_doc == -1)
	{
		free(cmd_line);
		return ;
	}
	if (ast->value.command->redir)
	{
		if (here_doc > 0)
			set_here_doc_fd();
		if (setup_redirections(ast->value.command->redir) != 0)
			exit (1);
	}
	execve(cmd_line, ast->value.command->cmd, get_env_array(&shelly));
	perror("Failed");
	exit(EXIT_FAILURE);
	return ;
}

void	exec_simple_pipe_left(t_ast_node *ast, t_shelly shelly, int fd_in, int *fd)
{
	if (fd_in != 0)
		dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_pipe_command(ast->value.pipe->left, shelly);
}

void	exec_pipe(t_ast_node *ast, t_shelly shelly, int fd_in)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
		exec_simple_pipe_left(ast, shelly, fd_in, fd);
	close(fd[1]);
	if (fd_in != 0)
		close(fd_in);
	if (ast->value.pipe->right->node_type == TOKEN_PIPE)
		exec_pipe(ast->value.pipe->right, shelly, fd[0]);
	else
	{
		if (fork() == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			exec_pipe_command(ast->value.pipe->right, shelly);
		}
		close(fd[0]);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}
