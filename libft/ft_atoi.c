/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:59:00 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/27 09:56:52 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		calc(long long int *n, int m, int sign)
{
	long long int t;

	t = *n * sign;
	if (sign == 1)
	{
		t = t * 10 + m;
		if (t < 0)
		{
			*n = -1;
			return (0);
		}
		*n = *n * 10 + m;
	}
	else
	{
		t = t * 10 - m;
		if (t > 0)
		{
			*n = 0;
			return (0);
		}
		*n = *n * 10 + m;
	}
	return (1);
}

int				ft_atoi(const char *str)
{
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		if (!calc(&n, *str - '0', sign))
			return ((int)n);
		str++;
	}
	n *= sign;
	return ((int)n);
}
