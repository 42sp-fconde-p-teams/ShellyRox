/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/06 22:24:23 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *value, t_bool *quoted_flag)
{
	char	*new_value;
	int		i;
	int		j;

	*quoted_flag = BOOL_FALSE;
	if (!value)
		return (NULL);
	new_value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	if (!new_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
		{
			*quoted_flag = BOOL_TRUE;
			i++;
			continue ;
		}
		new_value[j++] = value[i++];
	}
	new_value[j] = '\0';
	free(value);
	return (new_value);
}
