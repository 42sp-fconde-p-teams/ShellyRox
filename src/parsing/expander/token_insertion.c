/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_insertion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/06 18:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	insert_new_tokens(t_token **head, t_token *current, char **words)
{
	t_token	*new_token;
	t_token	*temp;
	int		i;

	i = 1;
	while (words[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return ;
		new_token->value = ft_strdup(words[i]);
		new_token->type = TOKEN_WORD;
		new_token->quoted = BOOL_FALSE;
		temp = current->next;
		current->next = new_token;
		new_token->prev = current;
		new_token->next = temp;
		if (temp)
			temp->prev = new_token;
		current = new_token;
		i++;
	}
	(void)head;
}
