/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:56:46 by fconde-p          #+#    #+#             */
/*   Updated: 2025/08/05 18:13:50 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	qty;

	qty = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			qty++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (qty);
}

static int	check_free_all(char **s, size_t j)
{
	if (!*s[j])
	{
		while (j > 0)
		{
			free(s[j]);
			j--;
		}
		free(s);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_s;
	size_t	start_i;
	size_t	i;
	int		j;

	splited_s = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!splited_s)
		return (NULL);
	i = 0;
	j = 0;
	start_i = 0;
	while (s[i] != '\0' && j < count_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start_i = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		splited_s[j] = ft_substr(s, start_i, i - start_i);
		if (!check_free_all(splited_s, j))
			return (NULL);
		j++;
	}
	splited_s[j] = NULL;
	return (splited_s);
}
