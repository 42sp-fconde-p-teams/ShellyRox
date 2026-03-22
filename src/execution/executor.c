/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by csila-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**find_path(char **envp)
{
	size_t i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(&envp[i][4], ':'));
		i++;
	}
	return (NULL);
}

void	executor(t_ast_node *ast, t_shelly shelly)
{
	// Se tiver pipe ou redirs no comando
	// fazer os dups
	// 	- Aplicar os redirects (se tiver) (setup_redirections)
	char	**path;

	path = find_path(shelly.envp);

	// executar o comando atual
	// se tiver pipe chama a recursão
	//
}
