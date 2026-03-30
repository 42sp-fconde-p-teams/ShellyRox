/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/27 00:30:58 by csilva-s         ###   ########.fr       */
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

	if (ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
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

int	exec_simple_command(t_ast_node *ast, t_shelly shelly)
{
	char	**path;
	char	*command_line;
	int		status;
	pid_t	pid;

	path = find_path(shelly.envp);
	command_line = find_command(path, ast->value.command->cmd[0]);
	if (!command_line)
	{
		// Free em tudo aqui <--
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (ast->value.command->redir)
		{
			if (setup_redirections(ast->value.command->redir) != 0)
				exit (1);
		}
		// Remover: Feat do framework de teste
		if (shelly.suppress_output)
		{
			int dev_null_fd = open("/dev/null", O_WRONLY);
			if (dev_null_fd != -1)
			{
				dup2(dev_null_fd, STDOUT_FILENO);
				dup2(dev_null_fd, STDERR_FILENO);
				close(dev_null_fd);
			}
		}
		execve(command_line, ast->value.command->cmd, shelly.envp);
		perror("Failed");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (status);
}
void	exec_pipe(t_ast_node *ast, t_shelly shelly)
{
	(void)ast;
	(void)shelly;
	return ;
}

int	executor(t_ast_node *ast, t_shelly shelly)
{
	int	status;

	if (ast->node_type == TOKEN_PIPE)
	{
		exec_pipe(ast, shelly);
	}
	else if (ast->node_type == TOKEN_WORD)
		status = exec_simple_command(ast, shelly);
	return (status);
}
