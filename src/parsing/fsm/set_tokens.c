/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/02/22 11:45:04 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../minishell.h"

static t_token	*create_token(char *value, t_token *next_t, t_token *prev_t)
{
	t_token	*token_node;

	token_node = NULL;
	token_node = ft_calloc(1, sizeof(t_token));
	token_node->value = value;
	token_node->next = next_t;
	token_node->prev = prev_t;
	// TODO set token_type from enum

	return (token_node);
}

t_token	*set_tokens(char *s)
{
	t_token	*new_token;

	new_token = NULL;
	new_token = create_token(s, NULL, NULL);

	return (new_token);
}