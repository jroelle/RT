/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:58:24 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 12:29:04 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*pos;
	const char	*npos;
	size_t		l;

	if (len == 0 && *needle == '\0')
		return ((char *)haystack);
	while ((l = len--))
	{
		pos = haystack++;
		npos = needle;
		while (1)
		{
			if (*npos == '\0')
				return ((char *)(haystack - 1));
			if (*npos != *pos && *pos == '\0')
				return (NULL);
			if (*npos != *pos)
				break ;
			npos++;
			pos++;
			if (l-- == 0)
				break ;
		}
	}
	return (NULL);
}
