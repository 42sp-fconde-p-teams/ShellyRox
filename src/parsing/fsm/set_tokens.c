/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/02/26 22:44:26 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static t_token	*create_token(char *value, t_token *prev_t)
{
	t_token	*token_node;

	token_node = NULL;
	token_node = ft_calloc(1, sizeof(t_token));
	token_node->value = value;
	token_node->next = NULL;
	token_node->prev = prev_t;
	// TODO set token_type from enum
	return (token_node);
}

t_token	*set_tokens(char *s)
{
	t_token	*head_n;
	t_token	*tail_n;
	t_token	*new_n;
	int		token_len;

	token_len = 0;
	head_n = NULL;
	tail_n = NULL;
	while (s && *s)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (!*s)
			break ;
		token_len = get_token_len(s);
		new_n = create_token(ft_substr(s, 0, token_len), tail_n);
		if (!head_n)
			head_n = new_n;
		if (tail_n)
			tail_n->next = new_n;
		tail_n = new_n;
		s += token_len;
	}
	return (head_n);
}
