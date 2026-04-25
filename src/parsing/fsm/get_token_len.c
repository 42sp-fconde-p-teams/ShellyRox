/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/25 20:06:29 by csilva-s         ###   ########.fr       */
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
		while (str[i] != quote)
			i++;
		i++;
		return (i);
	}
	if ((str[i] == '<' && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (2);
	while (str[i] != '\0')
	{
		if (is_token_delimiter(str[i]) == EXIT_SUCCESS)
			break ;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
