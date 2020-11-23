/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:38:10 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/23 18:57:59 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *s)
{
	size_t  length;

	if (s == 0)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strnew(size_t n)
{
	char 	*res;
	size_t 	i;

	if (!(res = malloc(sizeof(*res) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = '\0';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	char    *p_res;
	int             k;
	int             i;

	if (s1 == 0 || s2 == 0)
		return (0);
	p_res = malloc(sizeof(*p_res) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p_res == 0)
		return (0);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		p_res[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p_res[k++] = s2[i++];
	p_res[k] = '\0';
	return (p_res);
}

char    *ft_strdup(const char *s1)
{
	char    *p_s1;
	size_t  len;
	size_t  i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	p_s1 = malloc(sizeof(*p_s1) * (len + 1));
	if (p_s1 == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

char    *ft_strncpy(char *dst, char *src, size_t len)
{
	size_t  i;

	i = 0;
	while (i < len)
	{
		if (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		else
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		}
	}
	return (dst);
}
