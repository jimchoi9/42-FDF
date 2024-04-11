/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:38:34 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/08 21:40:08 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (0);
}

int	get_strlen(char *s)
{
	int	len;

	len = 0;
	if (!s || s[len] == '\0')
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	find_line(t_list *node)
{
	int	i;
	int	size;

	i = 0;
	size = get_strlen(node->buf);
	while (i < size)
	{
		if (node->buf[i] == '\n')
			break ;
		i++;
	}
	if (node->buf[i] == '\n')
		i++;
	return (i);
}

void	make_save(t_list *node, int size)
{
	int	i;

	i = 0;
	if (size == 0 || size == BUFFER_SIZE)
		return ;
	while (node->buf[size + i] != '\0')
	{
		node->save[i] = node->buf[i + size];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		node->save[i] = '\0';
		i++;
	}
}
