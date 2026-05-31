/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/30 20:46:41 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**set_env_var_array(t_env *curr, int count)
{
	int		i;
	char	**array;
	char	*s1;
	char	*s2;

	i = 0;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (curr)
	{
		s1 = ft_strjoin("=", curr->value);
		if (!s1)
			return (ft_free_array(array), NULL);
		s2 = ft_strjoin(curr->key, s1);
		free(s1);
		if (!s2)
			return (ft_free_array(array), NULL);
		array[i++] = s2;
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

	count = 0;
	curr = shell->env_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	curr = shell->env_list;
	array = set_env_var_array(curr, count);
	if (!array)
		return (NULL);
	return (array);
}
