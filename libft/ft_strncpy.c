/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:56:26 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:36:17 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		flag;

	flag = 1;
	i = 0;
	while (i < len)
	{
		if (flag)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		if (src[i] == '\0')
			flag = 0;
		i++;
	}
	return (dst);
}
