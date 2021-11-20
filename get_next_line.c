/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sjannet <sjannet@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:02:33 by Sjannet           #+#    #+#             */
/*   Updated: 2021/11/20 14:29:20 by Sjannet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *buf)
{
	int			read_line;
	char		*pointer;
	char		*line;
	char		*tmp;
	static char	*remainder;

	pointer = NULL;
	if (remainder)
		line = ft_strdup(remainder);
	else
		line = ft_strnew(1);

	while (!pointer && (read_line = read(fd, buf,  10)))
	{
		buf[read_line] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
		// tmp = NULL;
		if ((pointer = ft_strchr(line, '\n')))
		{
			*pointer = '\0';
			remainder = ft_strdup(++pointer);
		}
	}
	
	if (read_line == 0)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = get_line(fd, buf);
	free(buf);
	// buf = NULL;
	
	return (line);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
		printf("%s\n", line);
	return (0);
}