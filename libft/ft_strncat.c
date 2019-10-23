/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:56:48 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:36:04 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	int i;

	i = 0;
	while (dst[i] != '\0')
		i++;
	while (n > 0)
	{
		dst[i] = *src;
		n--;
		i++;
		if (*src == '\0')
			return (dst);
		src++;
	}
	dst[i] = '\0';
	return (dst);
}
