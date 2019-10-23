/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:59:00 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/05 14:58:44 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int				hex_len(const char *str)
{
	int i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') ||
			(str[i] >= 'a' && str[i] <= 'f') ||
			(str[i] >= 'A' && str[i] <= 'F'))
		i++;
	return (i);
}

static unsigned char	get_num(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	else
		return (10 + c - 'A');
}

unsigned				ft_htoi(const char *str)
{
	unsigned int	n;
	int				len;
	int				i;

	n = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str != '\0' && str[0] == '0' && str[1] == 'x')
		str = str + 2;
	len = hex_len(str);
	i = -1;
	n = 0;
	while (++i < len)
		n = n | (get_num(str[i]) << ((len - 1 - i) * 4));
	return (n);
}
