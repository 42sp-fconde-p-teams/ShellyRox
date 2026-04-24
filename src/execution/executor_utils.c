/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:58 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/22 21:45:40 by csilva-s         ###   ########.fr       */
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
		return (128 + WTERMSIG(status));
	return (status);
}

void	exec_command_in_child(t_ast_node *ast, t_shelly *shelly)
{
	int		builtin_ret;
	int		heredoc;
	char	*command_line;
	char	**env_arr;

	if (ast->value.command->cmd[0])
	{
		builtin_ret = execute_builtin(ast->value.command->cmd[0],
				ast->value.command->cmd, shelly);
		if (builtin_ret != -1)
			exit(builtin_ret);
		heredoc = check_here_doc(ast->value.command->redir);
		command_line = find_command(shelly, ast->value.command->cmd[0]);
		if (heredoc == -1 || !command_line)
			exit(handle_error(command_line, heredoc));
		env_arr = get_env_array(shelly);
		simple_command_routine(ast, command_line, env_arr, heredoc);
		free(command_line);
	}
}
