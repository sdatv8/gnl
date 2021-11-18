/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sjannet <sjannet@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:02:33 by Sjannet           #+#    #+#             */
/*   Updated: 2021/11/18 20:08:18 by Sjannet          ###   ########.fr       */
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	while (src[i])
		++i;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*buf;

	len = ft_strlen(s);
	if (!(buf = (char *)malloc(len + 1)))
		return (NULL);
	ft_strlcpy(buf, s, len + 1);
	return (buf);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
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

int		get_next_line(int fd, int BUFFER_SIZE)
{
	char		*line;
	char		*buf;
	static char	*remainder;
	char	*pointer;
	int		read_line;
	int		flag;

	if (remainder)
		line = ft_strdup(remainder);

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (flag && (read_line = read(fd, buf, BUFFER_SIZE)))
	{
		buf[read_line] = '\0';
		line = ft_strjoin(line, buf);
		if ((pointer = ft_strchr(line, '\n')))
		{
			*pointer = '\0';
			flag = 0;
			pointer++;
			remainder = ft_strdup(pointer);
		}

	}
	printf("%s", line);

	
	


	return (0);
}

int	main(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	// while (i < 4)
	// {
	get_next_line(fd, 10);
	printf("\n");
	get_next_line(fd, 10);
	printf("\n");
	get_next_line(fd, 10);
	printf("\n");
	get_next_line(fd, 10);
	// 	i++;
	// }
	// printf("%s\n", line);
	return (0);
}