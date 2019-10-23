/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:27:34 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:36:27 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		while (n > 0)
		{
			if (*s1 != *s2)
				return (0);
			if (*s1 == '\0')
				break ;
			s1++;
			s2++;
			n--;
		}
		return (1);
	}
	else
	{
		if (!s1 && !s2)
			return (1);
		else
			return (0);
	}
}
