/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:39:21 by csilva-s          #+#    #+#             */
/*   Updated: 2026/03/30 22:15:57 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shelly	shelly;
	char		*line;
	t_ast_node	*ast;

	if (argc < 1)
		return (1);
	(void)*argv;
	shelly.env_list = NULL;
	init_env_list(&shelly, envp);
	while (1)
	{
		t_token *tokens = NULL;
		line = readline("shelly🎀> ");
		if (!line)
			break ;
		tokens = set_tokens(line);
		tokens = expander(tokens, &shelly);
		ast = parser(&tokens);
		shelly.last_exit_status = executor(ast, shelly);
		add_history(line);
		free(line);
		// free everything function here
	}
	return (0);
}
