/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:26:08 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/05 18:04:57 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	if (end <= start)
	{
		ptr = ft_calloc(1, sizeof(char));
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	ptr = ft_calloc((end - start + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, (s1 + start), (end - start + 1));
	return (ptr);
}
