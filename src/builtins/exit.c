/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:18:08 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/24 14:49:38 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (BOOL_FALSE);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (BOOL_FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (BOOL_FALSE);
		i++;
	}
	return (BOOL_TRUE);
}

int	too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (255);
}

int	num_arg_required(void)
{
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	return (255);
}

int	ft_exit(t_shelly *shell, char **args)
{
	int	status;

	status = 0;
	if (!args || !args[0])
	{
		free_env_list(shell->env_list);
		free_tree(shell->ast);
		close(shell->saved_fd[0]);
		close(shell->saved_fd[1]);
		exit(0);
	}
	if (!args[1])
		status = shell->last_exit_status;
	else if (args[2])
		status = too_many_args();
	else
	{
		if (is_numeric(args[1]))
			status = ft_atoi(args[1]) & 255;
		else
			status = num_arg_required();
	}
	free_env_list(shell->env_list);
	free_tree(shell->ast);
	close(shell->saved_fd[0]);
	close(shell->saved_fd[1]);
	exit(status);
}
