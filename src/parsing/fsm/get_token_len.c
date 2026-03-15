/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/03/15 14:54:39 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
		if (str[i] == ' ' || str[i] == '|' || str[i] == '<' || str[i] == '>')
			break ;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
