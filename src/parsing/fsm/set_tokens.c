/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/02/22 16:56:41 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// static t_token	*create_token(char *value, t_token *next_t, t_token *prev_t)
// {
// 	t_token	*token_node;

// 	token_node = NULL;
// 	token_node = ft_calloc(1, sizeof(t_token));
// 	token_node->value = value;
// 	token_node->next = next_t;
// 	token_node->prev = prev_t;
// 	// TODO set token_type from enum
// 	return (token_node);
// }

t_token	*set_tokens(char *s)
{
	t_token	*curr_token;
	t_token	*tmp_token;
	int		token_len;

	token_len = 0;
	curr_token = NULL;
	tmp_token = NULL;
	// curr_token = create_token(s, NULL, NULL);
	while (*s)
	{
		// bypass initial spaces
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		// get current token length (with FSM)
		token_len = get_token_len(s);
		// extract substring (ft_substr())
		// create and add node to tokens list
		// go ahead on pointer
		s++;
	}
	return (curr_token);
}
