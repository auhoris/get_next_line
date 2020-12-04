/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:21:04 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/04 12:28:58 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	get_line(int fd, char **line, char **reminder)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*nl_ptr;
	int			bytes_read;
	char		*leakline;

	bytes_read = 0;
	if (treat_reminder(&(*reminder), line, &nl_ptr) == -1)
		return (-1);
	while (!nl_ptr && (bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (bytes_read <= 0)
			return (-1);
		buffer[bytes_read] = '\0';
		if ((nl_ptr = ft_nlpos(buffer)) != NULL)
			if (ft_checkbuf(&(*reminder), nl_ptr) == -1)
				return (-1);
		leakline = *line;
		if ((*line = ft_strjoin(*line, buffer)) == NULL)
			return (-1);
		free(leakline);
	}
	return ((nl_ptr) ? 1 : 0);
}

static void	lstclear(t_gnl **lst)
{
	t_gnl	*sv_lst;

	if (!(*lst))
		return ;
	while (*lst)
	{
		sv_lst = *lst;
		*lst = (*lst)->next;
		if ((*lst)->reminder)
			free((*lst)->reminder);
		free(sv_lst);
	}
	*lst = NULL;
}

int			get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*save_h;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (head == NULL)
		if (!(head = new_elem(fd)))
			return (-1);
	save_h = head;
	while (save_h->fd != fd)
	{
		if (save_h->next == NULL)
			if ((save_h->next = new_elem(fd)) == NULL)
			{
				lstclear(&head);
				return (-1);
			}
		save_h = save_h->next;
	}
	return (get_line(save_h->fd, line, &save_h->reminder));
}
