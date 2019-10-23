/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:33:00 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 11:30:23 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int unsigned	i;
	char			c;

	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		i = -n;
	}
	else
		i = n;
	if (i >= 10)
		ft_putnbr_fd(i / 10, fd);
	c = i % 10 + '0';
	write(fd, &c, 1);
}
