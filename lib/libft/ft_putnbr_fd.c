/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:12:48 by fconde-p          #+#    #+#             */
/*   Updated: 2025/10/08 20:41:45 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	*s;
	int		count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr_fd("-2147483648", fd);
		return (count);
	}
	else
		s = ft_itoa(n);
	if (!s)
		return (0);
	count += ft_putstr_fd(s, fd);
	free(s);
	return (count);
}
