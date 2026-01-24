/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:42:11 by fconde-p          #+#    #+#             */
/*   Updated: 2026/01/03 13:32:04 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nl_char(char *str)
{
	int	nl_index;

	if (str == NULL)
		return (-1);
	nl_index = 0;
	while (str[nl_index] != '\0' && str[nl_index] != '\n')
	{
		nl_index++;
	}
	if (str[nl_index] == '\0')
		nl_index = -1;
	else if (str[nl_index] == '\n')
		return (nl_index);
	return (-1);
}

static int	fill_buffer(int fd, char **buffer)
{
	char	*str_slice;
	int		bytes_read;
	char	*ptr_tmp;

	bytes_read = 0;
	str_slice = ft_calloc(GNL_BUFFER_SIZE + 1, sizeof(char));
	if (str_slice == NULL)
		return (1);
	while (get_nl_char(*buffer) < 0)
	{
		bytes_read = read(fd, str_slice, GNL_BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		str_slice[bytes_read] = '\0';
		ptr_tmp = ft_strjoin(*buffer, str_slice);
		free(*buffer);
		*buffer = ptr_tmp;
	}
	free(str_slice);
	return (bytes_read);
}

static char	*set_remain(char *buffer)
{
	char	*tmp;
	size_t	nl_index;
	size_t	b_size;

	if (!buffer)
		return (NULL);
	if (ft_strlen(buffer) == 0)
		return (buffer);
	nl_index = 0;
	b_size = (size_t)ft_strlen(buffer);
	nl_index = get_nl_char(buffer);
	tmp = NULL;
	tmp = ft_calloc(b_size - nl_index, sizeof(char));
	ft_strlcpy(tmp, (buffer + (int)nl_index) + 1, b_size - nl_index);
	free(buffer);
	buffer = tmp;
	return (buffer);
}

static char	*set_line(char **buffer)
{
	char	*return_ptr;

	return_ptr = NULL;
	if ((get_nl_char(*buffer) >= 0))
	{
		return_ptr = ft_calloc(get_nl_char(*buffer) + 2, sizeof(char));
		ft_strlcpy(return_ptr, *buffer, get_nl_char(*buffer) + 2);
		*buffer = set_remain(*buffer);
	}
	else if (get_nl_char(*buffer) < 0)
	{
		return_ptr = ft_calloc(ft_strlen(*buffer) + 1, sizeof(char));
		ft_strlcpy(return_ptr, *buffer, ft_strlen(*buffer) + 1);
		free(*buffer);
		*buffer = NULL;
	}
	return (return_ptr);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			eof;

	eof = 1;
	if (buffer == NULL)
		buffer = ft_calloc(1, 1);
	if (get_nl_char(buffer) < 0)
		eof = fill_buffer(fd, &buffer);
	if ((eof == 0 && ft_strlen(buffer) == 0) || eof < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = set_line(&buffer);
	return (line);
}
