/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/14 23:58:11 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier(char *str)
{
	int		i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if ((str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || 
			  (str[i] >= 'A' && str[i] <= 'Z') || 
			  (str[i] >= '0' && str[i] <= '9') || 
			  (str[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

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

static void	process_export_arg(char *arg, t_shelly *shell)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = eq + 1;
	}
	else
	{
		key = ft_strdup(arg);
		value = "";
	}
	if (!is_valid_identifier(key))
		ft_printf("minishell: export: '%s': not a valid identifier", key);
	else
		set_env_var(shell, key, value);
	free(key);
}

int	ft_export(char **args, t_shelly *shell)
{
	int	i;

	if (!args || !args[0])
		return (0);
	if (args[1] == NULL)
	{
		print_env_list(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], shell);
		i++;
	}
	return (0);
}
