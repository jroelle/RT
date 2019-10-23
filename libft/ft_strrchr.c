/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:57:51 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:38:04 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	const char *begin;

	begin = s;
	while (*s != '\0')
		s++;
	while (begin != s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
