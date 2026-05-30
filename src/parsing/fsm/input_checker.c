/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:28:49 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/30 17:01:39 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	input_checker(t_token *tokens)
{
	if (ft_strncmp(tokens->value, "|", 1) == 0)
	{
		printf("syntax error near unexpected token `%s'\n", tokens->value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}