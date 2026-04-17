/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_env_identifier.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:15:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_env_identifier(char *str)
{
	int		i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if ((str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || 
			  (str[i] >= 'A' && str[i] <= 'Z') || 
			  (str[i] >= '0' && str[i] <= '9') || 
			  (str[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}
