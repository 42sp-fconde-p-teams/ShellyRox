/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:28:49 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/28 10:53:12 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	input_checker(t_token *tokens)
{
	if (ft_strncmp(tokens->value, "|", 1) == 0)
	{
		printf("INPUT CHECKER FAIL: %s", tokens->value);
		return (EXIT_FAILURE);
	}
	printf("INPUT CHECKER SUCCESS: %s", tokens->value);
	return (EXIT_SUCCESS);
}