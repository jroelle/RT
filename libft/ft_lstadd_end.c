/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:33:11 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/03 13:11:47 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_end(t_list **head, t_list *node)
{
	t_list *tmp;

	if (head)
	{
		tmp = *head;
		if (tmp)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = node;
		}
		else
		{
			*head = node;
		}
	}
}
