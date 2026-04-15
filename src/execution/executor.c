/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/14 22:31:45 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(t_shelly *shell)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0 
			&& curr->key[4] == '\0')
			return (ft_split(curr->value, ':'));
		curr = curr->next;
	}
	return (NULL);
}
char	*find_command(char **path, char *cmd)
{
	char	*command_with_path;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if(access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = -1;
	while (path[++i] != NULL)
	{
		command_with_path = ft_strjoin(path[i], ft_strjoin("/", cmd));
		if (access(command_with_path, F_OK | X_OK) == 0)
			return (command_with_path);
		free(command_with_path);
	}
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

static int	execute_builtin(char *cmd, char **args, t_shelly *shelly)
{
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (ft_env(shelly));
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (ft_cd(args, shelly));
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (ft_exit(shelly, args));
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (ft_export(args, shelly));
	return (-1);
}

int	exec_simple_command(t_ast_node *ast, t_shelly shelly)
{
	char	*command_line;
	int		status;
	pid_t	pid;
	int		here_doc;
	char	**paths;

	if (ast->value.command->cmd[0] && execute_builtin(ast->value.command->cmd[0], ast->value.command->cmd, &shelly) != -1)
		return (0); 
	here_doc = check_here_doc(ast->value.command->redir);
	paths = find_path(&shelly);
	command_line = find_command(paths, ast->value.command->cmd[0]);
	if (paths)
		ft_free_array(paths);
	if (here_doc == -1)
	{
		free(command_line);
		return (1);
	}
	if (!command_line)
	{
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		char	**env_arr = get_env_array(&shelly);
		simple_command_routine(ast, command_line, env_arr, here_doc);
	}
	waitpid(pid, &status, 0);
	unlink("/tmp/.shelly_heredoc");
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
