/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 01:34:15 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/16 01:46:39 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_list(t_env *env)
{
	t_env *tmp;
	t_env *current;

	current = env;
	while (current != NULL)
	{
		tmp = current->next;
		free(current->value);
		free(current->key);
		free(current);
		current = tmp;
	}
	env = NULL;
}
