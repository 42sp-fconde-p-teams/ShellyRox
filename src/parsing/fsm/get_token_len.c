/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/02 19:49:56 by fconde-p         ###   ########.fr       */
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

// static int	check_assignment_operator(char *str, int i)
// {
// 	int	has_eq;
// 	int	j;

// 	has_eq = 0;
// 	j = 0;
// 	while (str[j] && j < i)
// 	{
// 		if (str[j] == '=')
// 			has_eq = 1;
// 		j++;
// 	}
// 	return (has_eq);
// }

static int	deal_with_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	get_token_len(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
		return (handle_quotes_len(&str[i]));
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		return (handle_operator_len(&str[i]));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (check_assignment_operator(str, i))
				i = deal_with_quote(str, i);
		}
		if (is_token_delimiter(str[i]) == EXIT_SUCCESS)
			break ;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}
