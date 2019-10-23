/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:25:22 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/27 09:36:08 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *mem;

	mem = NULL;
	if (size == (size_t)(-1))
		return ((void *)mem);
	if ((mem = (char *)malloc(size + 1)))
	{
		mem[size] = 0;
		while (size-- > 0)
			mem[size] = 0;
	}
	return ((void *)mem);
}
