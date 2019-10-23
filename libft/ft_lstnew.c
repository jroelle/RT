/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:32:27 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 10:30:09 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	node = NULL;
	if ((node = (t_list *)malloc(sizeof(t_list))))
	{
		node->content = NULL;
		node->content_size = 0;
		node->next = NULL;
		if (content != NULL)
		{
			node->content_size = content_size;
			if ((node->content = (void *)malloc(sizeof(char) * content_size)))
				ft_memcpy(node->content, content, content_size);
			else
			{
				free(node);
				node = NULL;
			}
		}
	}
	return (node);
}
