/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:32:09 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/12 14:02:33 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static t_info	*create_info(const int fd)
{
	t_info	*node;

	node = NULL;
	if ((node = (t_info *)malloc(sizeof(t_info))))
	{
		node->next = NULL;
		node->fd = fd;
		node->buf = NULL;
		node->len = 0;
		node->rlen = BUFF_SIZE;
	}
	return (node);
}

static int		write_buf(t_info *inf, char **line)
{
	char *p;

	if ((p = (ft_memchr(inf->buf, '\n', inf->len))))
	{
		*line = (char *)malloc(sizeof(char) * (p - inf->buf + 1));
		ft_memset(*line, '!', (p - inf->buf + 1));
		(*line)[p - inf->buf] = '\0';
		ft_memcpy(*line, inf->buf, p - inf->buf);
		if ((unsigned long long)(p - inf->buf) != (inf->len - 1))
		{
			ft_memmove(inf->buf, &inf->buf[p - inf->buf + 1],
						inf->len - (p - inf->buf + 1));
			inf->len = inf->len - (p - inf->buf + 1);
			return (1);
		}
	}
	else if (!(*line = ft_strndup(inf->buf, inf->len)))
		return (0);
	free(inf->buf);
	inf->buf = NULL;
	inf->len = 0;
	return (1);
}

static void		exclude(t_info **head, t_info **node)
{
	t_info *tmp;

	if (head != NULL && node != NULL && *head != NULL && *node != NULL)
	{
		tmp = *head;
		if (*head == *node)
			*head = (*node)->next;
		else
		{
			while (tmp && tmp->next != *node)
				tmp = tmp->next;
			if (tmp)
			{
				tmp->next = tmp->next->next;
				free(*node);
				*node = NULL;
			}
		}
	}
	if (*node)
	{
		free(*node);
		*node = NULL;
	}
}

static int		rline(int fd, t_info **head, t_info **i, char **line)
{
	char			buf[BUFF_SIZE];
	char			*p;

	if (!(p = ft_memchr((*i)->buf, '\n', (*i)->len)) && (*i)->rlen != 0)
	{
		if (((*i)->rlen = read(fd, buf, BUFF_SIZE)) >= 0)
		{
			if (!(*line = ft_memjoin((*i)->buf, (*i)->len, buf, (*i)->rlen)))
				return (-1);
			if ((*i)->buf)
				free((*i)->buf);
			(*i)->len = (*i)->len + (*i)->rlen;
			(*i)->buf = *line;
			return (-2);
		}
		else
			return (-1);
	}
	if (!p && (*i)->len == 0 && (*i)->rlen == 0)
	{
		exclude(head, i);
		return (0);
	}
	return (!write_buf(*i, line) ? -1 : 1);
}

int				ft_get_next_line(const int fd, char **line)
{
	static t_info	*head = NULL;
	t_info			*inf;
	int				r;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	inf = head;
	while (inf && inf->fd != fd)
		inf = inf->next;
	if (!inf)
	{
		if (!(inf = create_info(fd)))
			return (-1);
		inf->next = head;
		head = inf;
	}
	while ((r = rline(fd, &head, &inf, line)) == -2)
		;
	return (r);
}
