/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:21:04 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/01 21:39:22 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nlpos(char *str)
{
	int		i;
	char	*res;

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

static char	*get_line(char **reminder, char **line)
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

static void	ft_checkbuf(char **reminder, char *nl_ptr)
{
	char	*tmp;

	*nl_ptr = '\0';
	tmp = *reminder;
	*reminder = ft_strdup(++nl_ptr);
	if (tmp != NULL)
		free(tmp);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*nl_ptr;
	static char	*reminder;
	int			bytes_read;
	char		*leakline;

	bytes_read = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	nl_ptr = get_line(&reminder, line);
	while (!nl_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (bytes_read <= 0)
			return (-1);
		buffer[bytes_read] = '\0';
		if ((nl_ptr = ft_nlpos(buffer)) != NULL)
			ft_checkbuf(&reminder, nl_ptr);
		leakline = *line;
		*line = ft_strjoin(*line, buffer);
		free(leakline);
	}
	return ((nl_ptr) ? 1 : 0);
}
//int 	main(void)
//{
//	int 	fd;
//	char 	*line;
//	int	gnl;
//	int	number;
//
//	number = 1;
//	fd = open("fewchar_perline.txt", O_RDONLY);
//	while ((gnl = get_next_line(fd, &line)) > 0)
//	{
//		printf("gnl >> %d\n", gnl);
//		printf("%d: line >> %s\n", number, line);
//		free(line);
//		number++;
//	}
////	printf("gnl >> %d\n", gnl);
////	printf("line >> %s\n", line);
//	free(line);
//	//free(line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
////	printf("line >> %s\n", line);
////	free (line);
////	printf("get_next_line >> %d\n", get_next_line(fd, &line));
//	return (0);
//}
