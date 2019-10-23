/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:58:08 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:46:59 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *pos;
	const char *npos;

	if (*haystack == '\0' && *needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		pos = haystack;
		npos = needle;
		while (1)
		{
			if (*npos == '\0')
				return ((char *)haystack);
			if (*npos != *pos)
			{
				if (*pos == '\0')
					return (NULL);
				break ;
			}
			npos++;
			pos++;
		}
		haystack++;
	}
	return (NULL);
}
