/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by csila-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast_node	*parser(t_token **tokens)
{
	int i = 0;
	t_token **cpy_token = tokens;
	// just an idea (iterative)
	while (cpy_token[i])
	{
		if (cpy_token[i]->type == TOKEN_WORD)
		{
			// call create word node function
		}
		else if (cpy_token[i]->type == TOKEN_PIPE)
		{
			// call create pipe node function
		}
		else if (cpy_token[i]->type == TOKEN_REDIR_IN)
		{
			// call 'create redirect node' function
		}
		else if (cpy_token[i]->type = TOKEN_REDIR_OUT)
		{
			// call 'create redirect out node' function
		}
	}
	return (NULL);
}
