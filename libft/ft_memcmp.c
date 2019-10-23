/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:55:11 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 10:32:36 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
		if (((char *)s1)[i] != ((char *)s2)[i])
		{
			return ((unsigned char)(((char *)s1)[i]) -
				(unsigned char)(((char *)s2)[i]));
		}
	return (0);
}
