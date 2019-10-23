/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:26:40 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:35:21 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*ns;
	unsigned int	i;

	i = 0;
	ns = NULL;
	if (s)
	{
		while (s[i] != '\0')
			i++;
		if ((ns = (char *)malloc(sizeof(char) * (i + 1))))
		{
			i = 0;
			while (s[i] != '\0')
			{
				ns[i] = f(s[i]);
				i++;
			}
			ns[i] = '\0';
		}
	}
	return (ns);
}
