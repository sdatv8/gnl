/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sjannet <sjannet@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:02:33 by Sjannet           #+#    #+#             */
/*   Updated: 2021/10/31 18:11:03 by Sjannet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
		// if (!s1 || !s2)
	// 	return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\n')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int		get_next_line(int fd)
{
	char		*line;
	int			flag;
	char		buf[10 + 1];
	int			byte_was_read;
	
	flag = 1;
	while (flag && (byte_was_read = read(fd, buf, 10)))
	{
		buf[byte_was_read] = '\0';
		*line = *strjoin(line, buf);
		printf("r %s\n", line);
		if (ft_strchr(buf, '\n'))
			flag = 0;
	}
	printf("r %s\n", line);
	return (1);
}

int	main(void)
{
	int		fd;
	int		i;

	fd = open("text.txt", O_RDONLY);
	while (i < 2)
	{
		get_next_line(fd);
		i++;
	}
	
	return (0);
}