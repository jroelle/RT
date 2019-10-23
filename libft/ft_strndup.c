/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:55:49 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/03 13:10:57 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	int		i;

	if (!(dup = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	dup[n] = '\0';
	i = -1;
	while (s1[++i] != '\0' && n > 0)
	{
		dup[i] = s1[i];
		n--;
	}
	while (n-- > 0)
		dup[i++] = '\0';
	return (dup);
}
