/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:21:04 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/23 19:40:58 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#define BUFFER_SIZE 100

char 	*ft_nlpos(char *str)
{
	int 	i;
	char 	*res;

	i = 0;
	res = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			res = &str[i];
			return (res);
		}
		i++;
	}
	return (res);
}

void 	ft_strclr(char *str)
{
	if (str)
		while (*str)
			*str++ = '\0';
}

char 	*ft_treat_line(char *remind, char **line)
{
	char 	*n_ptr;
	char 	*temp;

	n_ptr = NULL;
	if (remind)
	{
		if ((n_ptr = ft_nlpos(remind)) != NULL)
		{
			*n_ptr = '\0';
			*line = ft_strdup(remind);
			temp = remind;
			n_ptr++;
			free (temp);
			ft_strncpy(remind, n_ptr, ft_strlen(n_ptr));
		}
		else
		{
			*line = ft_strdup(remind);
			ft_strclr(remind);
		}
	}
	else
		*line = ft_strnew(1);
	return (n_ptr);
}

int		get_next_line(int fd, char **line)
{
	int		bytes_read;
	char 	buffer[BUFFER_SIZE + 1];
	char 	*n_ptr;
	static char *remind;
	char 		*temp;

	n_ptr = ft_treat_line(remind, line);
	while (!n_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		if ((n_ptr = ft_nlpos(buffer)) != NULL)
		{
			*n_ptr = '\0';
			remind = ft_strdup(++n_ptr);
		}
		temp = *line;
		*line = ft_strjoin(*line, buffer);
		free (temp);
	}
	return (bytes_read);
}

int 	main(void)
{
	int 	fd;
	char 	*line;

	fd = open("file.txt", O_RDONLY);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	printf("line >> %s\n", line);
	free (line);
	return (0);
}
