/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/14 22:32:06 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sort_env_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strncmp(array[i], array[j], 1024) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env_list(t_shelly *shell)
{
	char	**env_array;
	int		i;

	env_array = get_env_array(shell);
	if (!env_array)
		return ;
	sort_env_array(env_array);
	i = 0;
	while (env_array[i])
	{
		ft_printf("%s\n", env_array[i]);
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

int	ft_export(char **args, t_shelly *shell)
{
	if (!args || !args[0])
		return (0);
	if (args[1] == NULL)
	{
		print_env_list(shell);
		return (0);
	}
	return (0);
}
