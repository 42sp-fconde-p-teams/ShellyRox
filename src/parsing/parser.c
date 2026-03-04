/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by csila-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parser(t_token **tokens)
{
	int i = 0;
	t_token **cpy_token = tokens;
	while (cpy_token[i])
	{
		if (cpy_token[i]->type == TOKEN_WORD)

	}
}
