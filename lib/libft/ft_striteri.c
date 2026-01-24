/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:57:52 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/04 18:51:17 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	size_s;
	unsigned int	i;

	if (!s || !f)
		return ;
	if (*s == '\0')
		return ;
	size_s = ft_strlen(s);
	i = 0;
	while (i < size_s)
	{
		f(i, &s[i]);
		i++;
	}
}
