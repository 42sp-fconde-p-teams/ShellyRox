/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_meaningful_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 17:18:39 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/03 17:21:42 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		has_meaningful_content(char *line)
{
	if (line[0] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
