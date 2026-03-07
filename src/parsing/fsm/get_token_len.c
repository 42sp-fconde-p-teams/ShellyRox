/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/03/01 19:47:28 by fconde-p         ###   ########.fr       */
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
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}
