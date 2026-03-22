/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:39:09 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/21 23:39:11 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_words_token(t_token *token)
{
	int count = 0;
	t_token *tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_APPEND)
			tmp = tmp->next;
		else if (tmp->type == TOKEN_WORD)
			count++;
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

char	*get_redir_filename(t_token *token)
{
	if (token->next && token->next->type == TOKEN_WORD)
		return (token->next->value);
	return (NULL);
}

t_redir	*add_node_linked(t_redir *redir, t_redir *redir_node)
{
	t_redir *tmp;

	tmp = redir;
	if (redir == NULL)
		return (redir_node);
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
	redir->next = NULL;
	redir->filename = get_redir_filename(*token);
	(*node)->value.command->redir = add_node_linked((*node)->value.command->redir, redir);
	*token = (*token)->next;
	if (*token && (*token)->type == TOKEN_WORD)
		*token = (*token)->next;
}

t_ast_node	*parse_command(t_token	**token)
{
	t_ast_node	*node;
	t_token	*tmp;
	int	i;

	node = malloc(sizeof(t_ast_node));
	tmp = *token;
	i = 0;
	if((*token)->type != TOKEN_PIPE)
	{
		node->node_type = (*token)->type;
		node->value.command = malloc(sizeof(t_command));
		node->value.command->redir = NULL;
		node->value.command->cmd = malloc(sizeof(char *) * (count_words_token(tmp) + 1));
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
	}
	*token = tmp;
	return (node);
}

t_ast_node	*parser(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*node;

	left = parse_command(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_PIPE)
		return (left);
	*tokens = (*tokens)->next;
	node = malloc(sizeof(t_ast_node));
	node->node_type = TOKEN_PIPE;
	node->value.pipe = malloc(sizeof(t_pipe));
	node->value.pipe->left = left;
	node->value.pipe->right = parser(tokens);
	return (node);
}
