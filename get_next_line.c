/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:21:04 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/01 18:56:41 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
//#define BUFFER_SIZE 100

char 	*ft_nlpos(char *str)
{
	int 	i;
	char 	*res;

	if (str == NULL)
		return (NULL);
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


char		*get_line(char **reminder, char **line)
{
	char	*tmp;
	char	*nl_ptr;

	nl_ptr = ft_nlpos(*reminder);
	if (nl_ptr != NULL)
	{
		*nl_ptr = '\0';
		*line = ft_strdup(*reminder);
		tmp = ft_strdup(++nl_ptr);
		free(*reminder);
		*reminder = tmp;
	}
	else if (*reminder != NULL)
	{
		*line = *reminder;
		*reminder = NULL;
	}
	else
		*line = ft_strdup("");
	return (nl_ptr);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*nl_ptr;
	static char	*reminder;
	int		bytes_read;
	char		*rem_tmp;
	char		*leakline;

	bytes_read = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
	{
		printf("here");
		return (-1);
	}
	nl_ptr = get_line(&reminder, line);
	while (!nl_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (bytes_read <= 0)
			return (-1);
		buffer[bytes_read] = '\0';
		if ((nl_ptr = ft_nlpos(buffer)) != NULL)
		{
			*nl_ptr = '\0';
			rem_tmp = ft_strdup(++nl_ptr);
			if (reminder != NULL)
				free(reminder);
			reminder = rem_tmp;
		}
		leakline = *line;
		*line = ft_strjoin(*line, buffer);
		free(leakline);
	}
	return (nl_ptr ? 1 : 0);
}

int 	main(void)
{
	int 	fd;
	char 	*line;
	int	gnl;

	fd = open("file2.txt", O_RDONLY);
	printf("HELLO");
	while ((gnl = get_next_line(2, &line)) > 0)
	{
		printf("gnl >> %d\n", gnl);
		printf("line >> %s\n", line);
		free(line);
	}
	printf("gnl >> %d\n", gnl);
	printf("line >> %s\n", line);
	//free(line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	printf("line >> %s\n", line);
//	free (line);
//	printf("get_next_line >> %d\n", get_next_line(fd, &line));
	return (0);
}
