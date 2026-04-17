/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/16 21:55:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

int	ft_unset(char **args, t_shelly *shell)
{
	t_env	*curr;
	t_env	*prev;
	char	*key;

	if (!args || !args[1])
		return (EXIT_SUCCESS);
	key = args[1];
	curr = shell->env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0 
			&& curr->key[ft_strlen(key)] == '\0')
		{
			if (prev == NULL)
				shell->env_list = curr->next;
			else
				prev->next = curr->next;
			free_env_node(curr);
			return (EXIT_SUCCESS);
		}
		prev = curr;
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
