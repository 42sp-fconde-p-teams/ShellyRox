/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2026/04/30 20:38:34 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *name, t_shelly *shell)
{
	t_env	*curr;

	if (!name || !shell || !shell->env_list)
		return (NULL);
	curr = shell->env_list;
	while (curr)
	{
		if (ft_strncmp(curr->key, name, ft_strlen(name)) == 0
			&& curr->key[ft_strlen(name)] == '\0')
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}
