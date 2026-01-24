/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:51:48 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/04 18:50:37 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size_s;
	char	*result;
	int		i;

	if (!s || !f)
		return (NULL);
	size_s = ft_strlen(s);
	result = ft_calloc(size_s + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < size_s)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
