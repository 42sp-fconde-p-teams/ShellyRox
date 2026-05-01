/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/30 21:28:04 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **args)
{
	int		i;
	t_bool	newline;

	if (!args)
		return (0);
	newline = BOOL_TRUE;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0 && args[1][2] == '\0')
	{
		newline = BOOL_FALSE;
		i = 2;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline == BOOL_TRUE)
		ft_printf("\n");
	return (0);
}
