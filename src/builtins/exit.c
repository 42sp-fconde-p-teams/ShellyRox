/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:18:08 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/31 19:52:39 by fconde-p         ###   ########.fr       */
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
	shell->should_close = BOOL_TRUE;
	if (!args || !args[0])
	{
		return (0);
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
	return (status);
}
