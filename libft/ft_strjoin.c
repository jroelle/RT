/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:30:21 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:34:34 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*newstr;

	newstr = NULL;
	if (s1 && s2)
	{
		i = 0;
		while (s1[i] != '\0')
			i++;
		j = 0;
		while (s2[j] != '\0')
			j++;
		if ((newstr = (char *)malloc(sizeof(char) * (i + j + 1))))
		{
			i = -1;
			while ((newstr[++i] = *s1))
				s1++;
			i--;
			while ((newstr[++i] = *s2))
				s2++;
		}
	}
	return (newstr);
}
