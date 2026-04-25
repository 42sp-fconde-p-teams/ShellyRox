/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:17:59 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/25 18:58:40 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_ast_node	*init_command_node(t_token **token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->value.command = malloc(sizeof(t_command));
	node->node_type = (*token)->type;
	node->value.command->redir = NULL;
	node->value.command->cmd = malloc(sizeof(char *) * (
				count_words_token(*token) + 1));
	return (node);
}

static t_ast_node	*process_command(t_token **token, t_ast_node *node)
{
	t_token		*tmp;
	int			i;

	i = 0;
	tmp = *token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_APPEND)
		{
			add_redir_command(&node, &tmp);
			continue ;
		}
		else
			node->value.command->cmd[i++] = tmp->value;
		if (tmp)
			tmp = tmp->next;
	}
	node->value.command->cmd[i] = NULL;
	return (node);
}

t_ast_node	*parse_command(t_token	**token)
{
	t_ast_node	*node;
	t_token		*tmp;

	tmp = *token;
	node = malloc(sizeof(t_ast_node));
	if ((*token)->type != TOKEN_PIPE)
	{
		node = init_command_node(token);
		node = process_command(token, node);
	}
	*token = tmp;
	return (node);
}
