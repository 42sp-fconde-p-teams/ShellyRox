/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:46:30 by fconde-p          #+#    #+#             */
/*   Updated: 2025/10/08 19:28:33 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		count += ft_putchar_fd(*s, fd);
		s++;
	}
	return (count);
}
