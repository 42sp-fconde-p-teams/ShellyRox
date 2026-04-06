/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/06 16:07:30 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(char **envp)
{
	size_t	i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}
char	*find_command(char **envp, char *cmd)
{
	char	*command_with_path;
	int		i;
	char	**path;
	char	*command;

	if (ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = -1;
	path = find_path(envp);
	command = ft_strjoin("/", cmd);
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

void	simple_command_routine(t_ast_node *ast, char *command_line, char **envp, int here_doc)
{
	if (ast->value.command->redir)
	{
		if (here_doc > 0)
			set_here_doc_fd();
		if (setup_redirections(ast->value.command->redir) != 0)
			exit (1);
	}
	// Remover: Feat do framework de teste
	// if (shelly.suppress_output)
	// {
	// 	int dev_null_fd = open("/dev/null", O_WRONLY);
	// 	if (dev_null_fd != -1)
	// 	{
	// 		dup2(dev_null_fd, STDOUT_FILENO);
	// 		dup2(dev_null_fd, STDERR_FILENO);
	// 		close(dev_null_fd);
	// 	}
	// }
	execve(command_line, ast->value.command->cmd, envp);
	perror("Failed");
	exit(EXIT_FAILURE);
}

int	exec_simple_command(t_ast_node *ast, t_shelly shelly)
{
	char	*command_line;
	int		status;
	pid_t	pid;
	int		here_doc;

	here_doc = check_here_doc(ast->value.command->redir);
	command_line = find_command(shelly.envp, ast->value.command->cmd[0]);
	if (here_doc == -1)
	{
		free(command_line);
		return (1);
	}
	if (!command_line)
	{
		// Free em tudo aqui <--
		return (127);
	}
	pid = fork();
	if (pid == 0)
		simple_command_routine(ast, command_line, shelly.envp, here_doc);
	waitpid(pid, &status, 0);
	unlink("/tmp/.shelly_heredoc");
	free(command_line);
	return (status);
}

int	executor(t_ast_node *ast, t_shelly shelly)
{
	int	status;

	status = 0;
	if (ast->node_type == TOKEN_PIPE)
		exec_pipe(ast, shelly, 0);
	else
		status = exec_simple_command(ast, shelly);
	return (status);
}
