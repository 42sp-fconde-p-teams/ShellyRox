/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:25:49 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/06 23:07:44 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*mapped_lst;

	if (!lst || !f || !del)
		return (NULL);
	mapped_lst = NULL;
	while (lst != NULL)
	{
		new_node = ft_lstnew(f(lst->content));
		ft_lstadd_back(&mapped_lst, new_node);
		if (!mapped_lst)
		{
			ft_lstclear(&mapped_lst, del);
		}
		lst = lst->next;
	}
	return (mapped_lst);
}
