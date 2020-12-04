/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:26:43 by auhoris           #+#    #+#             */
/*   Updated: 2020/12/04 12:49:22 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_gnl
{
	int				fd;
	char			*reminder;
	struct s_gnl	*next;
}				t_gnl;

size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
int				get_next_line(int fd, char **line);
char			*ft_nlpos(char *str);
t_gnl			*new_elem(int fd);

#endif
