/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:31:31 by lbradama          #+#    #+#             */
/*   Updated: 2018/12/15 18:53:53 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	len(unsigned n)
{
	if (n / 10 > 0)
		return (1 + len(n / 10));
	return (1);
}

static void	set_values(char *s, unsigned n, int *p, int end)
{
	if (end == 2)
		*p = *p + 1;
	if (n / 10 > 0)
		set_values(s, n / 10, p, 0);
	s[*p] = '0' + n % 10;
	*p = *p + 1;
	if (end == 1)
		s[*p] = ',';
	if (end == 2)
		s[*p] = '\0';
}

char		*ft_ftoa(float n, int accuracy)
{
	char			*str;
	int				m;
	int				a;
	int				b;

	m = 0;
	if (n < 0)
	{
		m = 1;
		n = -n;
	}
	a = (int)n;
	n = n - a;
	while (accuracy-- > 0)
		n *= 10;
	b = (int)n;
	str = NULL;
	if ((str = (char *)malloc(sizeof(char) * (1 + m + len(a) + len(b)))))
	{
		if (m)
			str[0] = '-';
		set_values(str, a, &m, 1);
		set_values(str, b, &m, 2);
	}
	return (str);
}
