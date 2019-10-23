/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:24:50 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/26 18:58:27 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *mem;

	mem = NULL;
	if ((mem = (char *)malloc(size)))
	{
		while (size-- > 0)
			mem[size] = 0;
	}
	return ((void *)mem);
}
