/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:32:54 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/23 15:32:58 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *cur;

	if (alst != NULL && *alst != NULL)
	{
		cur = *alst;
		while (cur)
		{
			tmp = cur->next;
			del(cur->content, cur->content_size);
			free(cur);
			cur = tmp;
		}
		*alst = NULL;
	}
}
