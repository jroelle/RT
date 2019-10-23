/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:57:09 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:34:42 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t res;

	i = 0;
	while (dst[i] != '\0')
		i++;
	if (i < size)
		res = i;
	else
		res = size;
	while (*src != '\0')
	{
		if (size > 0 && i < size - 1)
		{
			dst[i] = *src;
			i++;
		}
		src++;
		res++;
	}
	dst[i] = '\0';
	return (res);
}
