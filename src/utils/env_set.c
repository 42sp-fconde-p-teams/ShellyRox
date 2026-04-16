/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/12 21:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_env_var(t_shelly *shell, char *key, char *value)
{
	t_env	*curr;
	t_env	*last;
	t_env	*new_node;
	size_t	len;

	if (!shell || !key)
		return (0);
	len = ft_strlen(key);
	curr = shell->env_list;
	last = NULL;
	while (curr)
	{
		if (ft_strlen(curr->key) == len && ft_strncmp(curr->key, key, len) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value ? value : "");
			return (1);
		}
		last = curr;
		curr = curr->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value ? value : "");
	new_node->next = NULL;
	if (!last)
		shell->env_list = new_node;
	else
		last->next = new_node;
	return (1);
}
