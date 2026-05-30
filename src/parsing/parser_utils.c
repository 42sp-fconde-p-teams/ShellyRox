/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:39:44 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/24 12:05:22 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_ast_node	*init_cmd_node(t_token *token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = token->type;
	node->value.cmd = malloc(sizeof(t_command));
	if (!node->value.cmd)
		return (free(node), NULL);
	node->value.cmd->redir = NULL;
	node->value.cmd->cmd = malloc(sizeof(char *)
			* (count_words_token(token) + 1));
	if (!node->value.cmd->cmd)
	{
		free(node->value.cmd);
		free(node);
		return (NULL);
	}
	return (node);
}

static void	extract_cmd_tokens(t_ast_node *node, t_token **tmp)
{
	int	i;

	i = 0;
	while (*tmp && (*tmp)->type != TOKEN_PIPE)
	{
		if ((*tmp)->type == TOKEN_REDIR_IN || (*tmp)->type == TOKEN_REDIR_OUT
			|| (*tmp)->type == TOKEN_HEREDOC || (*tmp)->type == TOKEN_APPEND)
		{
			add_redir_command(&node, tmp);
			continue ;
		}
		node->value.cmd->cmd[i++] = ft_strdup((*tmp)->value);
		*tmp = (*tmp)->next;
	}
	node->value.cmd->cmd[i] = NULL;
}

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;
	t_token		*tmp;

	if (!token || !*token || (*token)->type == TOKEN_PIPE)
		return (NULL);
	node = init_cmd_node(*token);
	if (!node)
		return (NULL);
	tmp = *token;
	extract_cmd_tokens(node, &tmp);
	*token = tmp;
	return (node);
}
