/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/23 19:00:33 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char **set_env_var_array(t_env *curr, char *temp_val, int count)
{
	int i;
	char	**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (curr)
	{
		temp_val = ft_strjoin("=", curr->value);
		if (!temp_val)
			return (NULL);
		array[i++] = ft_strjoin(curr->key, temp_val);
		free(temp_val);
		curr = curr->next;
	}
	array[count] = NULL;
	return (array);
}

char	**get_env_array(t_shelly *shell)
{
	t_env	*curr;
	int		count;
	char	**array;
	char	*temp_val;

	count = 0;
	temp_val = NULL;
	curr = shell->env_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	curr = shell->env_list;
	array = set_env_var_array(curr, temp_val, count);
	if (!array)
		return (NULL);
	return (array);
}
