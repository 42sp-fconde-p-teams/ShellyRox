/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/25 20:18:50 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_elements(t_shelly *shell)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = shell->env_list;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

char	**get_env_array(t_shelly *shell)
{
	t_env	*curr;
	int		count;
	int		i;
	char	**array;
	char	*temp_val;

	count = count_elements(shell);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	curr = shell->env_list;
	while (curr)
	{
		temp_val = ft_strjoin("=", curr->value);
		if (!temp_val)
			return (NULL);
		array[i++] = ft_strjoin(curr->key, temp_val);
		free(temp_val);
		curr = curr->next;
	}
	array[i] = NULL;
	return (array);
}
