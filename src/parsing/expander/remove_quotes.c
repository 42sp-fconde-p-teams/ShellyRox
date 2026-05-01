/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/30 20:59:52 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	handle_quote_loop(char *value, char *new_value, t_bool *quoted_flag)
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	quote_type = 0;
	while (value[i])
	{
		if (quote_type == 0 && (value[i] == '\"' || value[i] == '\''))
		{
			quote_type = value[i];
			*quoted_flag = BOOL_TRUE;
			i++;
			continue ;
		}
		else if (quote_type != 0 && value[i] == quote_type)
		{
			quote_type = 0;
			i++;
			continue ;
		}
		new_value[j++] = value[i++];
	}
	new_value[j] = '\0';
}

char	*remove_quotes(char *value, t_bool *quoted_flag)
{
	char	*new_value;

	*quoted_flag = BOOL_FALSE;
	if (!value)
		return (NULL);
	new_value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	if (!new_value)
		return (NULL);
	handle_quote_loop(value, new_value, quoted_flag);
	free(value);
	return (new_value);
}
