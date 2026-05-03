/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:39:21 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/03 17:04:50 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		has_meaningful_content(char *line)
{
	if (line[0] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	do_shelly(t_shelly shelly)
{
	char		*line;
	t_ast_node	*ast;
	t_token		*tokens;
	t_token		*token_head;

	while (1)
	{
		line = readline("shelly🎀> ");
		if (has_meaningful_content(line) == EXIT_FAILURE)
		{
			free(line);
			continue ;
		}
		tokens = NULL;
		tokens = set_tokens(line);
		token_head = tokens;
		tokens = expander(tokens, &shelly);
		ast = parser(&tokens);
		shelly.last_exit_status = executor(ast, &shelly);
		free_tree(ast);
		clear_token_list(&token_head);
		add_history(line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shelly	shelly;

	if (argc < 1)
		return (1);
	(void)*argv;
	shelly.env_list = NULL;
	init_env_list(&shelly, envp);
	do_shelly(shelly);
	free_env_list(shelly.env_list);
	return (shelly.last_exit_status);
}
