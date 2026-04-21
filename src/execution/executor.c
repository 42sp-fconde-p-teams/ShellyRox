/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/21 19:20:57 by csilva-s         ###   ########.fr       */
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
	char	*command;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	command = search_cmd_path(cmd, shelly);
	if (!command)
		return (NULL);
	return (command);
}

void	simple_command_routine(t_ast_node *ast, char *command_line,
		char **envp, int here_doc)
{
	if (ast->value.command->redir)
	{
		if (here_doc > 0)
			set_here_doc_fd();
		if (setup_redirections(ast->value.command->redir) != 0)
			exit (1);
	}
	execve(command_line, ast->value.command->cmd, envp);
	perror("Failed");
	exit(EXIT_FAILURE);
}

int	exec_simple_command(t_ast_node *ast, t_shelly *shelly)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_command_in_child(ast, shelly);
	return (get_status_code(pid));
}

int	executor(t_ast_node *ast, t_shelly *shelly)
{
	int	status;

	status = 0;
	if (ast->node_type == TOKEN_PIPE)
		exec_pipe(ast, shelly, 0);
	else
		status = exec_simple_command(ast, shelly);
	return (status);
}
