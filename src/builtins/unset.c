/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/30 21:27:29 by csilva-s         ###   ########.fr       */
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

static void	unset_variable(char *key, t_shelly *shell)
{
	t_env	*curr;
	t_env	*prev;

	if (!validate_env_identifier(key))
	{
		ft_printf("minishell: unset: '%s': not a valid identifier\n", key);
		return ;
	}
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
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **args, t_shelly *shell)
{
	int	i;

	if (!args)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		unset_variable(args[i], shell);
		i++;
	}
	return (EXIT_SUCCESS);
}
