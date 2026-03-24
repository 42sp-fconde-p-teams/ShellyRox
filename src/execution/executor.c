/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/23 23:37:35 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(char **envp)
{
	size_t i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}
char	*find_command(char **path, char *cmd)
{
	char	*command;
	char	*command_with_path;
	int		i;

	if (access(cmd, F_OK | X_OK) != 0)
		return (NULL);
	if (ft_strchr(cmd, '/') && (access(cmd, F_OK | X_OK) != 0))
		return (cmd);
	command = ft_strjoin("/", cmd);
	i = 0;
	while (path[i] != NULL)
	{
		command_with_path = ft_strjoin(path[i], command);
		if (access(command_with_path, F_OK | X_OK) == 0)
		{
			free(command);
			return (command_with_path);
		}
		free(command_with_path);
		i++;
	}
	free(command);
	return (NULL);
}

int	executor(t_ast_node *ast, t_shelly shelly)
{
	char	**path;
	char	*command_line;
	int		pid;
	int		status; // código de saída
	// Aplicar os redirects (se tiver) (setup_redirections) <--
	
	path = find_path(shelly.envp);
	command_line = find_command(path, ast->value.command->cmd[0]);
	if (!command_line)
	{
		// Free em tudo aqui <--
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(command_line, ast->value.command->cmd, shelly.envp);
		perror("Failed");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (status);
	// executar o comando atual
	// se tiver pipe chama a recursão
}
