/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:44:57 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		validate_array_helper(char **str, int *count,
				int *comma)
{
	*str = validate_json_skip_empty(*str);
	if (!*str || **str == ']')
		return (0);
	*comma = 0;
	if (**str == ',')
	{
		*comma = 1;
		if (!*count)
			return (0);
		(*str)++;
	}
	else if (**str == '"' || **str == '-' ||
		(**str >= '0' && **str <= '9') || **str == '[' || **str == '{')
	{
		*str = validate_get_str(*str);
		if (!*str)
			return (0);
		(*count)++;
	}
	else
		return (0);
	return (1);
}

char	*validate_json_read_array(char *str, int *size)
{
	int count;
	int comma;

	comma = 0;
	count = 0;
	if (*str == '[')
	{
		str++;
		while (*str && *str != ']')
		{
			if (!validate_array_helper(&str, &count, &comma))
				break ;
		}
		if (!str || *str != ']')
			return (NULL);
		if (size != NULL)
			*size = count;
		str++;
		return (str);
	}
	return (NULL);
}

int		validate_object_helper_helper(char **str, int *state)
{
	*state = 3;
	if (**str == '"' || (**str == '-') || (**str >= '0' &&
		**str <= '9') || **str == '[' || **str == '{')
	{
		*str = validate_get_str(*str);
		if (!*str)
			return (0);
	}
	else
		return (0);
	return (1);
}

int		validate_object_helper_next(char **str, int *state)
{
	if (*state == 1)
	{
		if (!validate_json_state(state, 2, **str == ':'))
			return (0);
		(*str)++;
	}
	else if (*state == 2)
	{
		if (!validate_object_helper_helper(str, state))
			return (0);
	}
	else if (*state == 3)
	{
		if (!validate_json_state(state, 0, **str == ','))
			return (0);
		(*str)++;
	}
	return (1);
}

int		validate_object_helper(char **str, int *state)
{
	*str = validate_json_skip_empty(*str);
	if (!*str || **str == '}')
		return (0);
	if (*state == 0)
	{
		*str = validate_json_read_string(*str);
		if (!*str)
			return (0);
		*state = 1;
	}
	else if (*state >= 1 && *state <= 3)
		if (!validate_object_helper_next(str, state))
			return (0);
	return (1);
}
