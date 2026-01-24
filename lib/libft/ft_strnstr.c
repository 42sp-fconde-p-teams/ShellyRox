/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:15:56 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/26 17:26:04 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	if (ft_strlen(little) > ft_strlen(big) || len == 0)
		return (NULL);
	if (len == 1)
	{
		if (big[0] == *little)
			return (((char *)&big[i]));
		else
			return (NULL);
	}
	while (big[i] != '\0' && i < len - 1)
	{
		if (ft_strncmp(&big[i], little, ft_strlen(little)) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
