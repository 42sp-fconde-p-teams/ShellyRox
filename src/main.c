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

#include "../includes/minishell.h"

// Iniciar uma copia do envp. (envp é a cópia de todas as variáveis de ambiente do sistema)
// Iniicar o loop de leitura da linha .
// 		capturar a entrada (se retornar NULL, o user mandou um CTRL + D.
// 		se a linha e vazia da free() e continue.
// 		add_history() pra adicionar a linha no historico.
// 			(MOCK COM PRINTF PRA SABER SE ESTA CHEGANDO NO FLUXO DO LEXER).
//		limpar a memoria.
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
		line = readline("shelly🎀> ");
		if (!line)
			break ;
		add_history(line);
		printf("%s\n", line);
		free(line);
	}
	free(shelly.envp);
	return (0);
}
