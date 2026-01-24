/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:36:29 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:55:35 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	size_t			i;

	i = 0;
	ptr_s = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (ptr_s[i] == (unsigned char)c)
			return ((char *)&ptr_s[i]);
		else
			i++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
