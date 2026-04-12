/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:40:19 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/09 21:45:53 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_shelly *shelly)
{
	int	i = 0;

	while (shelly && shelly->envp && shelly->envp[i])
	{
		ft_putstr_fd(shelly->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
