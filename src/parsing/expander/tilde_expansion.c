/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/30 20:59:43 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*expand_tilde(char *value, t_shelly *shelly)
{
	char	*home_path;
	char	*expanded_value;

	if (!value || value[0] != '~')
		return (ft_strdup(value));
	home_path = get_env_value("HOME", shelly);
	if (!home_path)
		return (ft_strdup(value));
	if (ft_strlen(value) == 1)
		expanded_value = ft_strdup(home_path);
	else if (value[1] == '/')
		expanded_value = ft_strjoin(home_path, value + 1);
	else
		expanded_value = ft_strdup(value);
	free(home_path);
	return (expanded_value);
}
