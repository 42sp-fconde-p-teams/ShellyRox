/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/01 20:02:06 by fconde-p         ###   ########.fr       */
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

static int	handle_quotes_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i];
	i++;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

static int	handle_operator_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
		return (1);
	else if (str[0] == '<' && str[1] == '<')
		return (2);
	else if (str[0] == '>' && str[1] == '>')
		return (2);
	else if (str[0] == '<' || str[0] == '>')
		return (1);
	else
		return (-1);
}

static int	has_assignment_operator(char *str, int i)
{

}

int	get_token_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
		return (handle_quotes_len(&str[i]));
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (handle_operator_len(&str[i]));
	while (str[i] != '\0' && !is_token_delimiter(str[i]))
	{
		if ((str[i] == '\'' || str[i] == '\"') 
			&& has_assignment_operator(&str, i))
		{
			i += handle_quotes_len(&str[i]);
		}
		if (is_token_delimiter(str[i]) == EXIT_SUCCESS)
			break ;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
