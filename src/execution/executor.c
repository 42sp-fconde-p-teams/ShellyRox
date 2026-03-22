/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:38:29 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/21 23:38:38 by csilva-s         ###   ########.fr       */
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
	char	**path;
	// Aplicar os redirects (se tiver) (setup_redirections)

	path = find_path(shelly.envp);
	
	// executar o comando atual
	// se tiver pipe chama a recursão
}
