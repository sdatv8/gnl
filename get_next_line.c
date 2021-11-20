/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sjannet <sjannet@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:02:33 by Sjannet           #+#    #+#             */
/*   Updated: 2021/11/20 10:48:26 by Sjannet          ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(sizeof(*s) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
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

	flag = 1;
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
			pointer++;
			remainder = ft_strdup(pointer);
			flag = 0; //break
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
	while (i < 20)
	{
		get_next_line(fd, 10);
		printf("\n");
		i++;
	}
	// printf("%s\n", line);
	return (0);
}