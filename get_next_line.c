/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sjannet <sjannet@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:02:33 by Sjannet           #+#    #+#             */
/*   Updated: 2021/11/28 14:47:03 by Sjannet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reading_buf(int fd, char *buf, char *remainder)
{
	int	read_buf;

	read_buf = 1;
	while (read_buf != 0 && ft_strchr(remainder, '\n') == NULL)
	{
		read_buf = read(fd, buf, BUFFER_SIZE);
		if (read_buf < 0)
		{
			free (buf);
			return (0);
		}
		buf[read_buf] = '\0';
		if (remainder)
			remainder = ft_strjoin(remainder, buf);
		else
			remainder = ft_substr(buf, 0, read_buf);
	}
	free(buf);
	return (remainder);
}

char	*get_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = ft_substr(remainder, 0, i);
	return (line);
}

char	*get_remainder(char *remainder)
{
	int		i;
	char	*ret_remainder;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	i++;
	ret_remainder = ft_substr(remainder, i, ft_strlen(remainder));
	free (remainder);
	return (ret_remainder);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	remainder = reading_buf(fd, buf, remainder);
	if (!remainder || remainder[0] == '\0')
	{
		free(remainder);
		remainder = 0;
		return (0);
	}
	line = get_line(remainder);
	if (!line || line[0] == '\0')
	{
		free (line);
		return (0);
	}
	remainder = get_remainder(remainder);
	return (line);
}
