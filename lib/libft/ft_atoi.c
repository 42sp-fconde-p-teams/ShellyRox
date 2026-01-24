/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:02:19 by fconde-p          #+#    #+#             */
/*   Updated: 2025/07/27 18:52:14 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gen_int(char *ptr, int acc)
{
	while (ft_isdigit(*ptr) > 0)
	{
		acc = acc * 10 + (*ptr - '0');
		ptr++;
	}
	return (acc);
}

static int	check_sign(char *ptr, int *sign)
{
	if (*ptr == '-' || *ptr == '+')
	{
		if (ft_isdigit(*(ptr + 1)) == 0)
			return (0);
		if (*ptr == '-')
			*sign = -1;
		ptr++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	acc;
	int	*ptr_sign;

	ptr_sign = &sign;
	sign = 1;
	acc = 0;
	while (*nptr >= 0 && *nptr <= 32)
		nptr++;
	if (ft_isalpha(*nptr))
		return (0);
	if (!check_sign((char *)nptr, ptr_sign))
		return (0);
	while (*nptr)
	{
		if (ft_isdigit(*nptr) > 0)
		{
			acc = gen_int((char *)nptr, acc);
			return (acc * sign);
		}
		nptr++;
	}
	return (acc * sign);
}
