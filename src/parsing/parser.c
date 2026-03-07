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

int	count_words_token(t_token *token)
{
	int count = 0;
	t_token *tmp = token;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_redir	*add_node_linked(t_redir *redir, t_redir *redir_node)
{
	t_redir *tmp;

	tmp = redir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = redir_node;
	return (redir);
}

void	add_redir_command(t_ast_node **node, t_token **token)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	redir->type = (*token)->type;
	redir->filename = (*token)->value;
	(*node)->value.command->redir = add_node_linked((*node)->value.command->redir, redir);
}

t_ast_node	*parse_command(t_token	*token)
{
	t_ast_node	*node;
	t_token	*tmp;
	int	i;

	node = malloc(sizeof(t_ast_node));
	tmp = token;
	i = 0;
	if(token->type != TOKEN_PIPE)
	{
		node->node_type = token->type;
		node->value.command = malloc(sizeof(t_command));
		node->value.command->cmd = malloc(sizeof(char *) * (count_words_token(tmp) + 1));
		while (tmp && tmp->type != TOKEN_PIPE)
		{
			if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
				|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_APPEND)
				add_redir_command(&node, &tmp);
			else
				node->value.command->cmd[i++] = tmp->value;
			tmp = tmp->next;
		}
		node->value.command->cmd[i] = NULL;
	}
	return (node);
}

t_ast_node	*parser(t_token *tokens)
{
	t_ast_node	*node;
	t_token	*tmp;

	tmp = tokens;
	node = malloc(sizeof(t_ast_node));
	node->node_type = tokens->type;
	if (node->node_type == TOKEN_PIPE)
	{
		node->value.pipe = malloc(sizeof(t_pipe));
		node->value.pipe->left = parse_command(tmp);
		node->value.pipe->right = parser(tmp->next);
	}
	else
		node = parse_command(tmp);
	return (node);
}
