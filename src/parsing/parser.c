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

t_ast_node	*create_ast_node_word(t_token *token)
{
	int i;
	t_token *tmp;
	t_ast_node *node;

	i = 0;
	tmp = token;
	node = malloc(sizeof(t_ast_node));
	node->value.command = malloc(sizeof(t_command));
	node->value.command->cmd = malloc(sizeof(char *) * (count_words_token(token) + 1));
	if (tmp->type == TOKEN_WORD)
	{
		node->node_type = TOKEN_WORD;
		while (tmp != NULL && tmp->type == TOKEN_WORD)
		{
			node->value.command->cmd[i++] = tmp->value;
			tmp = tmp->next;
		}
		node->value.command->cmd[i] = NULL;
	}
	return (node);
}

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

void	print_ast(t_ast_node *node)
{
	if (node == NULL)
		return;
	if (node->node_type == TOKEN_WORD)
	{
		int i = 0;
		while (node->value.command->cmd[i])
			printf("%s ", node->value.command->cmd[i++]);
		printf("\n");
	}
	else if (node->node_type == TOKEN_PIPE)
	{
		print_ast(node->value.pipe->left);
		print_ast(node->value.pipe->right);
	}
}

int	parser(t_token *tokens)
{
	t_ast_node *root = create_ast_node_word(tokens);
	if (root != NULL)
	{
		print_ast(root);
		return (0);
	}
	return (1);
}
