/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/15 00:10:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_env_array(t_shelly *shell)
{
	t_env	*curr;
	int		count;
	int		i;
	char	**array;
	char	*temp_val;

	count = 0;
	curr = shell->env_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	curr = shell->env_list;
	while (curr)
	{
		temp_val = ft_strjoin("=", curr->value);
		if (!temp_val)
			return (NULL); // Simplified error handling for brevity
		array[i++] = ft_strjoin(curr->key, temp_val);
		free(temp_val);
		curr = curr->next;
	}
	array[i] = NULL;
	return (array);
}
