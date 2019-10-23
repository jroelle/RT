/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:31:22 by lbradama          #+#    #+#             */
/*   Updated: 2018/11/25 12:52:40 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char			*get_substring(const char *s,
					unsigned int start, unsigned int finish)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	sub = NULL;
	if ((sub = (char *)malloc(sizeof(char) * (finish - start + 1))))
	{
		while (start + i < finish)
		{
			sub[i] = s[start + i];
			i++;
		}
		sub[i] = '\0';
	}
	return (sub);
}

static int			get_substrings(char **arr, const char *s, char c)
{
	unsigned int a;
	unsigned int i;
	unsigned int p;

	a = 0;
	i = 0;
	p = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (p != i)
				if (!(arr[a++] = get_substring(s, p, i)))
					return (a--);
			p = ++i;
		}
		else
			i++;
	}
	if (p != i)
		if (!(arr[a++] = get_substring(s, p, i)))
			return (a--);
	return (-1);
}

static unsigned int	get_split_length(char const *s, char c)
{
	unsigned int i;
	unsigned int n;
	unsigned int p;

	i = 0;
	n = 0;
	p = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (p != i)
				n++;
			p = ++i;
		}
		else
			i++;
	}
	if (p != i)
		n++;
	return (n);
}

static int			check_on_err(char **arr, int n)
{
	if (n >= 0)
	{
		while (n-- > 0)
		{
			free(arr[n]);
			arr[n] = NULL;
		}
		return (0);
	}
	return (1);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	n;
	char			**arr;

	arr = NULL;
	if (s)
	{
		if (*s == '\0')
			n = 0;
		else if (*s == '\0')
			n = 1;
		else
			n = get_split_length(s, c);
		if ((arr = (char **)malloc(sizeof(*arr) * (n + 1))))
		{
			arr[n] = NULL;
			if (!check_on_err(arr, get_substrings(arr, s, c)))
			{
				free(arr);
				arr = NULL;
			}
		}
	}
	return (arr);
}
