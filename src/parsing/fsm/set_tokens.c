/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:25 by fconde-p          #+#    #+#             */
/*   Updated: 2026/02/22 11:10:26 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../minishell.h"

t_token	*set_tokens(char *s)
{
	t_token	*token_node;

	token_node = NULL;
	token_node = ft_calloc(1, sizeof(t_token));
	token_node->value = s;

	return (token_node);
}