/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:58 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/23 15:27:44 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(t_shelly *shelly)
{
	char	**path;
	t_env	*tmp;

	path = NULL;
	tmp = shelly->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			path = ft_split(tmp->value, ':');
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

int	handle_error(char *command_line, int heredoc)
{
	free(command_line);
	if (heredoc == -1)
		return (1);
	return (127);
}

int	get_status_code(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	unlink("/tmp/.shelly_heredoc");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	return (status);
}

int	exec_builtin_parent(t_ast_node *ast, t_shelly *shelly)
{
	int	saved_fd[2];
	int	builtin_ret;

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	if (ast->value.cmd->redir != NULL)
		setup_redirections(ast->value.cmd->redir);
	builtin_ret = execute_builtin(ast->value.cmd->cmd[0],
			ast->value.cmd->cmd, shelly);
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
	return (builtin_ret);
}

void	exec_command_in_child(t_ast_node *ast, t_shelly *shelly)
{
	int		builtin_ret;
	int		heredoc;
	char	*command_line;
	char	**env_arr;

	if (ast->value.cmd->cmd[0])
	{
		builtin_ret = execute_builtin(ast->value.cmd->cmd[0],
				ast->value.cmd->cmd, shelly);
		if (builtin_ret != -1)
			exit(builtin_ret);
		heredoc = 0;
		command_line = find_command(shelly, ast->value.cmd->cmd[0]);
		if (heredoc == -1||!command_line)
			exit(handle_error(command_line, heredoc));
		env_arr = get_env_array(shelly);
		simple_command_routine(ast, command_line, env_arr, heredoc);
		ft_free_array(env_arr);
		free(command_line);
	}
}
