/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:27:00 by fconde-p          #+#    #+#             */
/*   Updated: 2025/10/08 19:24:31 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int nbr, char case_opt)
{
	unsigned int	div;
	unsigned int	mod;
	char			c_nbr;
	char			*base;
	int				count;

	count = 0;
	if (case_opt == 'x')
		base = "0123456789abcdef";
	if (case_opt == 'X')
		base = "0123456789ABCDEF";
	if (case_opt != 'x' && case_opt != 'X')
		return (0);
	if (nbr >= 16)
	{
		div = nbr / 16;
		count += ft_puthex(div, case_opt);
	}
	mod = nbr % 16;
	c_nbr = base[mod];
	count += write(1, &c_nbr, 1);
	return (count);
}
