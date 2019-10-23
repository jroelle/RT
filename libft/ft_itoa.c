/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:31:31 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 10:29:17 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_len(unsigned n)
{
	if (n / 10 > 0)
		return (1 + get_len(n / 10));
	return (1);
}

static void	set_values(char *s, unsigned n, int *p, int end)
{
	if (n / 10 > 0)
		set_values(s, n / 10, p, 0);
	s[*p] = '0' + n % 10;
	*p = *p + 1;
	if (end)
		s[*p] = '\0';
}

char		*ft_itoa(int n)
{
	char			*str;
	int				m;
	unsigned int	num;

	m = 0;
	if (n < 0)
	{
		m = 1;
		num = -n;
	}
	else
		num = n;
	str = NULL;
	if ((str = (char *)malloc(sizeof(char) * (1 + m + get_len(num)))))
	{
		if (m)
			str[0] = '-';
		set_values(str, num, &m, 1);
	}
	return (str);
}
