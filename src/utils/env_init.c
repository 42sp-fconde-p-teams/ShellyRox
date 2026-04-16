/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/12 21:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_env_list(t_shelly *shell, char **envp)
{
	int		i;
	char	*str;
	char	*eq;

	i = 0;
	if (!shell || !envp)
		return (0);
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		if (!str)
			return (0);
		eq = ft_strchr(str, '=');
		if (eq)
		{
			*eq = '\0';
			set_env_var(shell, str, eq + 1);
		}
		free(str);
		i++;
	}
	return (1);
}
