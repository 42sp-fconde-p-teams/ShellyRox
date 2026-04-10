/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:40:19 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/09 21:19:41 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_shelly shelly)
{
	int	i = 0;

	while (shelly.envp && shelly.envp[i])
	{
		printf("%s\n", shelly.envp[i]);
		i++;
	}
	return (0);
}
