/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 21:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/23 22:03:59 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_env	*set_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

static void	set_last_node(t_env *last, t_shelly *shell, t_env *new_node)
{
	if (!last)
		shell->env_list = new_node;
	else
		last->next = new_node;
}

static int	update_env_var(t_env *curr, char *key, char *value)
{
	size_t	len;

	len = ft_strlen(key);
	if (ft_strlen(curr->key) == len && ft_strncmp(curr->key, key, len) == 0)
	{
		free(curr->value);
		if (value)
			curr->value = ft_strdup(value);
		else
			curr->value = ft_strdup("");
		return (1);
	}
	return (0);
}

int	set_env_var(t_shelly *shell, char *key, char *value)
{
	t_env	*curr;
	t_env	*last;

	if (!shell || !key)
		return (0);
	curr = shell->env_list;
	last = NULL;
	while (curr)
	{
		if (update_env_var(curr, key, value))
			return (1);
		last = curr;
		curr = curr->next;
	}
	return (set_last_node(last, shell, set_new_node(key, value)), 1);
}
