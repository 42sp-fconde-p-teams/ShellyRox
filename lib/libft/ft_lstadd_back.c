/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:30:07 by fconde-p          #+#    #+#             */
/*   Updated: 2025/12/25 19:41:18 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		new->previous = NULL;
		*lst = new;
	}
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new;
		new->previous = last_node;
	}
}
