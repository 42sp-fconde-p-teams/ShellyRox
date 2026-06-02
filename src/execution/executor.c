/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/31 18:26:45 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*search_cmd_path(char *cmd, t_shelly *shelly)
{
	char	*command;
	char	**path;
	char	*command_with_path;
	int		i;

	path = find_path(shelly);
	if (!path)
		return (NULL);
	command = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i] != NULL)
	{
		command_with_path = ft_strjoin(path[i], command);
		if (access(command_with_path, F_OK | X_OK) == 0)
		{
			ft_free_array(path);
			free(command);
			return (command_with_path);
		}
		free(command_with_path);
	}
	ft_free_array(path);
	free(command);
	return (NULL);
}

char	*find_command(t_shelly *shelly, char *cmd)
{
	char	*full_command;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	full_command = search_cmd_path(cmd, shelly);
	if (!full_command)
	{
		printf("%s: No such file or directory\n", cmd);
		return (NULL);
	}
	return (full_command);
}

void	simple_command_routine(t_ast_node *ast, char *command_line,
		char **envp)
{
	if (ast->value.cmd->redir)
		set_here_doc_fd();
	execve(command_line, ast->value.cmd->cmd, envp);
	perror("Failed");
	exit(EXIT_FAILURE);
}

int	exec_simple_command(t_ast_node *ast, t_shelly *shelly)
{
	pid_t	pid;
	int		status;

	if (is_builtin(ast->value.cmd->cmd[0]))
		return (exec_builtin_parent(ast, shelly));
	setup_signals(SIG_STATE_IGNORE);
	pid = fork();
	if (pid == 0)
	{
		setup_signals(SIG_STATE_CHILD);
		exec_command_in_child(ast, shelly);
	}
	status = get_status_code(pid);
	setup_signals(SIG_STATE_INTERACTIVE);
	return (status);
}

int	executor(t_ast_node *ast, t_shelly *shelly)
{
	int	status;

	status = 0;
	if (ast->node_type == TOKEN_PIPE)
	{
		exec_pipe(ast, shelly, 0);
		status = shelly->last_exit_status;
	}
	else
		status = exec_simple_command(ast, shelly);
	return (status);
}
