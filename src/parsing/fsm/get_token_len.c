/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/26 23:04:41 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_token_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>'
		|| c == '\t' || c == '\n'
		|| c == '\"' || c == '\'')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	get_token_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i];
		i++;
		while (str[i] != '\0' && str[i] != quote)
			i++;
		if (str[i] == quote)
			i++;
		return (i);
	}
	if ((str[i] == '<' && str[i + 1] == '<') 
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (2);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			int	has_eq = 0;
			int	j = 0;
			while (str[j] && j < i)
			{
				if (str[j] == '=')
					has_eq = 1;
				j++;
			}
			if (has_eq)
			{
				quote = str[i];
				i++;
				while (str[i] != '\0' && str[i] != quote)
					i++;
				if (str[i] == quote)
					i++;
				continue ;
			}
		}
		if (is_token_delimiter(str[i]) == EXIT_SUCCESS)
			break ;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
