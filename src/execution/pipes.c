/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:50 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/24 11:32:40 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pipe_command(t_ast_node *ast, t_shelly *shelly)
{
	char	*cmd_line;
	int		here_doc;
	int		builtin_ret;
	char	**env_arr;

	if (ast->value.cmd->cmd[0])
	{
		builtin_ret = execute_builtin(ast->value.cmd->cmd[0],
				ast->value.cmd->cmd, shelly);
		if (builtin_ret != -1)
			ft_exit(shelly, NULL);
	}
	here_doc = check_here_doc(ast->value.cmd->redir, shelly);
	cmd_line = find_command(shelly, ast->value.cmd->cmd[0]);
	if (here_doc == -1 || !cmd_line)
		exit(handle_error(cmd_line, here_doc));
	env_arr = get_env_array(shelly);
	simple_command_routine(ast, cmd_line, env_arr, here_doc);
	return ;
}

void	exec_simple_pipe_left(t_ast_node *ast, t_shelly *shelly,
			int fd_in, int *fd)
{
	if (fd_in != 0)
		dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_pipe_command(ast->value.pipe->left, shelly);
}

void	exec_pipe_recursive(t_ast_node *ast, t_shelly *shelly, int fd_in)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		setup_signals(SIG_STATE_CHILD);
		exec_simple_pipe_left(ast, shelly, fd_in, fd);
	}
	close(fd[1]);
	if (fd_in != 0)
		close(fd_in);
	if (ast->value.pipe->right->node_type == TOKEN_PIPE)
		exec_pipe_recursive(ast->value.pipe->right, shelly, fd[0]);
	else
	{
		if (fork() == 0)
		{
			setup_signals(SIG_STATE_CHILD);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			exec_pipe_command(ast->value.pipe->right, shelly);
		}
		close(fd[0]);
	}
}

void	exec_pipe(t_ast_node *ast, t_shelly *shelly, int fd_in)
{
	setup_signals(SIG_STATE_IGNORE);
	exec_pipe_recursive(ast, shelly, fd_in);
	while (waitpid(-1, NULL, 0) > 0)
		;
	setup_signals(SIG_STATE_INTERACTIVE);
}
