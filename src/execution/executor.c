/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/30 22:42:58 by csilva-s         ###   ########.fr       */
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

int	check_here_doc(t_redir *redir)
{
	int	fd;
	t_redir	*tmp;

	tmp = redir;
	fd = 0;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			fd = open("/tmp/.shelly_heredoc", O_WRONLY | O_CREAT | O_TRUNC , 0600);
			if (fd == -1)
				return (-1);
			read_and_write_here_doc(fd, tmp);
		}
		tmp = tmp->next;
	}
	return (fd);
}

void	read_and_write_here_doc(int fd, t_redir *redir)
{
	char *line;

	ft_putstr_fd("> ", 0);
	while ((line = get_next_line(0)))
	{
		if (ft_strncmp(line, ft_strjoin(redir->filename, "\n\0"),
			ft_strlen(redir->filename) + 2) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("> ", 0);
	}
	close (fd);
}

void	set_here_doc_fd(void)
{
	int fd;

	fd = open("/tmp/.shelly_heredoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	exec_simple_command(t_ast_node *ast, t_shelly shelly)
{
	char	**path;
	char	*command_line;
	int		status;
	pid_t	pid;
	int		here_doc;

	here_doc = check_here_doc(ast->value.command->redir);
	path = find_path(shelly.envp);
	command_line = find_command(path, ast->value.command->cmd[0]);
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
	{
		if (ast->value.command->redir)
		{
			if (here_doc > 0)
				set_here_doc_fd();
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
	unlink("/tmp/.shelly_heredoc");
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

	status = 0;
	if (ast->node_type == TOKEN_PIPE)
		exec_pipe(ast, shelly);
	else
		status = exec_simple_command(ast, shelly);
	return (status);
}
