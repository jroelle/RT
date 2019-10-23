/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:33:36 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/28 11:09:40 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	del(void *content, size_t content_size)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
	if (content_size)
		content_size = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *tmp;
	t_list *cur;

	head = NULL;
	cur = NULL;
	while (lst)
	{
		tmp = f(lst);
		if ((!cur && !(cur = ft_lstnew(tmp->content, tmp->content_size))) ||
			(cur && !(cur->next = ft_lstnew(tmp->content, tmp->content_size))))
		{
			ft_lstdel(&head, &del);
			return (head);
		}
		if (head == NULL)
			head = cur;
		else
			cur = cur->next;
		lst = lst->next;
	}
	return (head);
}
