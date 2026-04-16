/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:39:21 by csilva-s          #+#    #+#             */
/*   Updated: 2026/04/16 01:41:12 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shelly	shelly;
	char		*line;
	t_ast_node	*ast;
	t_token		*tokens;
	t_token		*token_head;

	if (argc < 1)
		return (1);
	(void)*argv;
	shelly.env_list = NULL;
	init_env_list(&shelly, envp);
	while (1)
	{
#ifdef TESTER
		if (!isatty(fileno(stdin)))
		{
			char	*raw;
			raw = get_next_line(fileno(stdin));
			if (!raw)
				break ;
			line = ft_strtrim(raw, "\n");
			free(raw);
		}
		else
			line = readline("shelly🎀> ");
#else
		line = readline("shelly🎀> ");
#endif
		if (!line)
			break ;
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
	free_env_list(shelly.env_list);
	return (shelly.last_exit_status);
}
