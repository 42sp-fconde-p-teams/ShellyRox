/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/05 11:17:04 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static void	set_type(t_token *token)
{
	if (ft_strncmp(token->value, "|", 1) == EXIT_SUCCESS)
		token->type = TOKEN_PIPE;
	else if (ft_strncmp(token->value, "<<", 2) == EXIT_SUCCESS)
		token->type = TOKEN_HEREDOC;
	else if (ft_strncmp(token->value, ">>", 2) == EXIT_SUCCESS)
		token->type = TOKEN_APPEND;
	else if (ft_strncmp(token->value, "<", 1) == EXIT_SUCCESS)
		token->type = TOKEN_REDIR_IN;
	else if (ft_strncmp(token->value, ">", 1) == EXIT_SUCCESS)
		token->type = TOKEN_REDIR_OUT;
	else if (token->value[0] == '\"' || token->value[0] == '\'')
	{
		token->type = TOKEN_WORD;
		token->quoted = BOOL_TRUE;
	}
	else
	{
		token->type = TOKEN_WORD;
		token->quoted = BOOL_FALSE;
	}
}
static t_token	*create_token(char *value, t_token *prev_t)
{
	t_token	*token_node;

	token_node = NULL;
	token_node = ft_calloc(1, sizeof(t_token));
	token_node->value = value;
	token_node->next = NULL;
	token_node->prev = prev_t;
	// TODO set token_type from enum
	set_type(token_node);
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
