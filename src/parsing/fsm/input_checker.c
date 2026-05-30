/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:28:49 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/30 17:16:37 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	input_checker(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (EXIT_SUCCESS);
	if (tokens->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `%s'\n", tokens->value);
		return (EXIT_FAILURE);
	}
	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE)
		{
			if (!curr->next || curr->next->type == TOKEN_PIPE)
			{
				printf("syntax error near unexpected \
					token `%s'\n", curr->value);
				return (EXIT_FAILURE);
			}
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
