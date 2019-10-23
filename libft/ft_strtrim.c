/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:31:10 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/22 18:31:12 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	char			*newstr;

	i = 0;
	newstr = NULL;
	if (s)
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		if (s[i] != '\0')
		{
			while (s[i + 1] != '\0')
				i++;
			while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
				i--;
			i++;
		}
		if ((newstr = (char *)malloc(sizeof(char) * (i + 1))))
		{
			newstr[i] = '\0';
			while (i-- > 0)
				newstr[i] = s[i];
		}
	}
	return (newstr);
}
