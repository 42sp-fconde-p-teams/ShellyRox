/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:12:31 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/28 21:08:47 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if ((s1_size == 0 && s2_size == 0))
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		ft_memset(ptr, 0, 1);
		return (ptr);
	}
	ptr = ft_calloc((s1_size + s2_size + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcat(ptr, s1, s1_size + 1);
	ft_strlcat(ptr, s2, s1_size + s2_size + 1);
	return (ptr);
}
