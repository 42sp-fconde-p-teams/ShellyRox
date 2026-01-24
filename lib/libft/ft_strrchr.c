/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:09:49 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/25 20:54:44 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;

	size = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[size]);
	while (size > 0)
	{
		if (s[size -1] == (unsigned char)c)
			return ((char *)&s[size - 1]);
		else
			size--;
	}
	return (NULL);
}
