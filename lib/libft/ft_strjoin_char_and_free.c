/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char_and_free.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:12:31 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/05 10:12:47 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char_and_free(char *s1, char c)
{
	char	*char_str;
	char	*new_str;

	char_str = (char *)ft_calloc(2, sizeof(char));
	if (!char_str)
		return (NULL);
	char_str[0] = c;
	new_str = ft_strjoin(s1, char_str);
	free(s1);
	free(char_str);
	return (new_str);
}
