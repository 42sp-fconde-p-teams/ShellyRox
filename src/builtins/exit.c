/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:18:08 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/12 18:30:20 by fconde-p         ###   ########.fr       */
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

int	ft_exit(t_shelly *shell, char **args)
{
	int	status;

	if (!args || !args[0])
		exit(0);
	if (args[1] && !args[2])
	{
		if (is_numeric(args[1]))
			status = ft_atoi(args[1]) & 255;
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			status = 255;
		}
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		status = 255;
	}
	else
		status = shell->last_exit_status;
	exit(status);
}
