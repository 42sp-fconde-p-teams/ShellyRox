/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 22:18:57 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/23 22:38:57 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	expected_len;

	i = 0;
	j = 0;
	expected_len = ft_strlen(dst) + ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	while (dst[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i++] = src[j++];
	}
	dst[i++] = '\0';
	return (expected_len);
}
