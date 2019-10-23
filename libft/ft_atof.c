/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:59:00 by lbradama          #+#    #+#             */
/*   Updated: 2019/01/31 18:09:32 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	calc(const char *str, double *n, int sign)
{
	double	f;

	if (*str == '.')
	{
		f = 1;
		str++;
		while (*str != '\0' && *str >= '0' && *str <= '9')
		{
			*n = *n * 10 + (*str - '0') * sign;
			f *= 10;
			str++;
		}
		*n = *n / f;
	}
}

double		ft_atof(const char *str)
{
	double	n;
	int		sign;

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
		n = n * 10 + (*str - '0') * sign;
		str++;
	}
	calc(str, &n, sign);
	return (n);
}
