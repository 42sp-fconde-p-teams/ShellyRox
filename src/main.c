/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 23:39:21 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/24 17:00:43 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_line(char *line, t_shelly *shelly)
{
	t_token		*tokens;
	t_token		*token_head;
	t_ast_node	*ast;

	shelly->ast = NULL;
	tokens = set_tokens(line);
	token_head = tokens;
	tokens = expander(tokens, shelly);
	ast = parser(&tokens);
	find_heredoc(ast, shelly);
	shelly->last_exit_status = executor(ast, shelly);
	free_tree(ast);
	clear_token_list(&token_head);
	shelly->ast = NULL;
	add_history(line);
	free(line);
}

void	do_shelly(t_shelly *shelly)
{
	char		*line;

	while (1)
	{
		line = readline("shelly🎀> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (has_meaningful_content(line) == EXIT_FAILURE)
		{
			free(line);
			continue ;
		}
		process_line(line, shelly);
		if (shelly->should_close == BOOL_TRUE)
			exit(shelly->last_exit_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shelly	shelly;

	if (argc < 1)
		return (1);
	(void)*argv;
	shelly = (t_shelly){0};
	init_env_list(&shelly, envp);
	setup_signals(SIG_STATE_INTERACTIVE);
	do_shelly(&shelly);
	rl_clear_history();
	free_env_list(shelly.env_list);
	return (shelly.last_exit_status);
}
