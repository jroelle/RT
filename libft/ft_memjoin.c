/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:54:40 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/03 13:11:33 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memjoin(void *s1, size_t l1, void *s2, size_t l2)
{
	char	*dst;
	size_t	i;

	dst = NULL;
	if ((l1 && !s1) || (l2 && !s2))
		return ((void *)dst);
	dst = (char *)malloc(l1 + l2 + 1);
	i = 0;
	while (l1--)
	{
		dst[i] = *((char *)s1);
		s1++;
		i++;
	}
	while (l2--)
	{
		dst[i] = *((char *)s2);
		s2++;
		i++;
	}
	dst[i] = 0;
	return ((void *)dst);
}
