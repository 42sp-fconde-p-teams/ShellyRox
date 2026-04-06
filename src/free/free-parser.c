/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:48 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/06 16:00:12 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir *next;
	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}

void	free_tree(t_ast_node *ast)
{
	if (!ast)
		return ;
	if (ast->node_type == TOKEN_PIPE)
	{
		free_tree(ast->value.pipe->left);
		free_tree(ast->value.pipe->right);
		free(ast->value.pipe);
	}
	else
	{
		free_redir(ast->value.command->redir);
		free(ast->value.command->cmd);
		free(ast->value.command);
	}
	free(ast);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
