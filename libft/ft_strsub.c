/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:27:46 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:38:46 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	newstr = NULL;
	if (s)
	{
		if ((newstr = (char *)malloc(sizeof(char) * (len + 1))))
		{
			i = 0;
			while (len-- > 0 && s[start] != '\0')
			{
				newstr[i] = s[start];
				start++;
				i++;
			}
			newstr[i] = '\0';
		}
	}
	return (newstr);
}
