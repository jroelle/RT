/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:44:38 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		validate_json_state(int *state, int new_state,
				int check)
{
	if (check)
		*state = new_state;
	else
		return (0);
	return (1);
}

char	*validate_json_skip_empty(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

char	*validate_json_read_string(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		if (*str != '"')
			return (NULL);
		str++;
		return (str);
	}
	return (NULL);
}

char	*validate_json_read_number(char *str)
{
	if (*str == '-')
		str++;
	if (*str >= '0' && *str <= '9')
	{
		while (*str >= '0' && *str <= '9')
			str++;
		if (*str == '.')
		{
			str++;
			while (*str >= '0' && *str <= '9')
				str++;
			if (*(str - 1) == '.')
				return (NULL);
		}
		return (str);
	}
	return (NULL);
}

char	*validate_get_str(char *str)
{
	char *res;

	if (*str == '"')
		res = validate_json_read_string(str);
	else if ((*str == '-') || (*str >= '0' && *str <= '9'))
		res = validate_json_read_number(str);
	else if (*str == '[')
		res = validate_json_read_array(str, NULL);
	else
		res = validate_json_read_object(str);
	return (res);
}
