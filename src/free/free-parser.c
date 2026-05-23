/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:33:48 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/23 15:27:44 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*next;

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
		free_redir(ast->value.cmd->redir);
		free(ast->value.cmd->cmd);
		free(ast->value.cmd);
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
