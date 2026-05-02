/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assignment_operator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:09:55 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/02 19:10:20 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_assignment_operator(char *str, int i)
{
	int	has_eq;
	int	j;

	has_eq = 0;
	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '=')
			has_eq = 1;
		j++;
	}
	return (has_eq);
}
