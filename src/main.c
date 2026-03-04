/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2026/02/18 12:17:20 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shelly;
	char	*line;

	if (argc < 1)
		return (1);
	(void)*argv;
	shelly.envp = envp;
	while (1)
	{
		t_token *tokens = NULL;
		parser(tokens);
		line = readline("shelly🎀> ");
		if (!line)
			break ;
		add_history(line);
		free(line);
	}
	free(shelly.envp);
	return (0);
}
