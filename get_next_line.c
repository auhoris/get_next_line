/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:21:04 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/02 22:41:26 by auhoris          ###   ########.fr       */
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

static int	treat_reminder(char **reminder, char **line, char **nl_ptr)
{
	char	*tmp;

	*nl_ptr = ft_nlpos(*reminder);
	if (*nl_ptr != NULL)
	{
		**nl_ptr = '\0';
		if ((*line = ft_strdup(*reminder)) == NULL ||
				(tmp = ft_strdup(++(*nl_ptr))) == NULL)
			return (-1);
		free(*reminder);
		*reminder = tmp;
	}
	else if (*reminder != NULL)
	{
		*line = *reminder;
		*reminder = NULL;
	}
	else
	{
		if ((*line = ft_strdup("")) == NULL)
			return (-1);
	}
	return (0);
}

static int	ft_checkbuf(char **reminder, char *nl_ptr)
{
	char	*tmp;

	*nl_ptr = '\0';
	tmp = *reminder;
	if ((*reminder = ft_strdup(++nl_ptr)) == NULL)
		return (-1);
	if (tmp != NULL)
		free(tmp);
	return (0);
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
	if (treat_reminder(&reminder, line, &nl_ptr) == -1)
		return (-1);
	while (!nl_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (bytes_read <= 0)
			return (-1);
		buffer[bytes_read] = '\0';
		if ((nl_ptr = ft_nlpos(buffer)) != NULL)
			if (ft_checkbuf(&reminder, nl_ptr) == -1)
				return (-1);
		leakline = *line;
		if ((*line = ft_strjoin(*line, buffer)) == NULL)
			return (-1);
		free(leakline);
	}
	return ((nl_ptr) ? 1 : 0);
}
