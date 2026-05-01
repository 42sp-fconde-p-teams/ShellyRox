/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:40:19 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/30 21:29:18 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_shelly *shelly)
{
	t_env	*curr;

	if (!shelly || !shelly->env_list)
		return (0);
	curr = shelly->env_list;
	while (curr)
	{
		ft_putstr_fd(curr->key, 1);
		ft_putstr_fd("=", 1);
		if (curr->value)
			ft_putstr_fd(curr->value, 1);
		else
			ft_putstr_fd("", 1);
		ft_putstr_fd("\n", 1);
		curr = curr->next;
	}
	return (0);
}
