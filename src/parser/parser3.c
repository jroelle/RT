/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:45:30 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*validate_json_read_object(char *str)
{
	int state;

	if (*str == '{')
	{
		str++;
		state = 0;
		while (*str && *str != '}')
			if (!validate_object_helper(&str, &state))
				break ;
		if (state != 3 || !str || *str != '}')
			return (NULL);
		str++;
		return (str);
	}
	return (NULL);
}

void	get_keys_helper_helper(char **str, int *state)
{
	*state = 3;
	if (**str == '"')
		*str = validate_json_read_string(*str);
	else if ((**str == '-') || (**str >= '0' && **str <= '9'))
		*str = validate_json_read_number(*str);
	else if (**str == '[')
		*str = validate_json_read_array(*str, NULL);
	else if (**str == '{')
		*str = validate_json_read_object(*str);
}

int		get_keys_helper(char **str, int *state, int *count)
{
	*str = validate_json_skip_empty(*str);
	if (!*str || **str == '}')
		return (0);
	if (*state == 0)
	{
		*str = validate_json_read_string(*str);
		(*count)++;
		*state = 1;
	}
	else if (*state == 1)
	{
		validate_json_state(state, 2, **str == ':');
		(*str)++;
	}
	else if (*state == 2)
		get_keys_helper_helper(str, state);
	else if (*state == 3)
	{
		validate_json_state(state, 0, **str == ',');
		(*str)++;
	}
	return (1);
}

int		get_keys_count(char *str)
{
	int count;
	int state;

	count = 0;
	if (*str == '{')
	{
		str++;
		state = 0;
		while (*str && *str != '}')
			if (!get_keys_helper(&str, &state, &count))
				break ;
	}
	return (count);
}

void	parse_array_helper_1(char **str, t_json *array, int *i)
{
	char *tmp;

	tmp = *str;
	*str = validate_json_read_string(*str);
	(*(array + *i)).type = 2;
	(*(array + *i)).value = ft_strnew(*str - tmp);
	ft_strncpy((*(array + *i)).value, tmp, *str - tmp);
	(*i)++;
}
