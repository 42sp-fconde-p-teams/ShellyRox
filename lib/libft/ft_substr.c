/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:16:17 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/28 20:07:21 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	sub_len;

	s_len = ft_strlen(s);
	if (start > (s_len - 1))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		ft_memset(substr, 0, 1);
		return (substr);
	}
	if (len > (s_len - start))
		sub_len = s_len - start;
	else
		sub_len = len;
	substr = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, sub_len);
	substr[sub_len] = '\0';
	return (substr);
}
