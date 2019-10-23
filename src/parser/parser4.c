/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:46:07 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_array_helper_2(char **str, t_json *array, int *i)
{
	char *tmp;

	tmp = *str;
	*str = validate_json_read_number(*str);
	(*(array + *i)).type = 1;
	(*(array + *i)).value = ft_strnew(*str - tmp);
	ft_strncpy((*(array + *i)).value, tmp, *str - tmp);
	(*i)++;
}

int		parse_array_helper_3(char **str, t_json *array, int *i)
{
	t_json	*ptr;

	if (**str == '[')
	{
		(*(array + *i)).type = 3;
		if (!json_parse_array(str, &((*(array + *i)).data),
			&((*(array + *i)).size)))
			return (0);
		(*i)++;
	}
	else if (**str == '{')
	{
		(*(array + *i)).type = 0;
		ptr = &(*(array + *i));
		if (!json_parse_object(str, &ptr))
			return (0);
		(*i)++;
	}
	return (1);
}

int		parse_array_helper(char **str, t_json *array, int *i)
{
	*str = validate_json_skip_empty(*str);
	if (!*str || **str == ']')
		return (-1);
	if (**str == ',')
		(*str)++;
	else if (**str == '"')
		parse_array_helper_1(str, array, i);
	else if ((**str == '-') || (**str >= '0' && **str <= '9'))
		parse_array_helper_2(str, array, i);
	else if (**str == '[' || **str == '{')
	{
		if (!parse_array_helper_3(str, array, i))
			return (0);
	}
	else
		return (-1);
	return (1);
}

int		json_parse_array(char **source, t_json **data, int *count)
{
	t_json	*array;
	char	*str;
	int		i;
	int		r;

	str = *source;
	array = NULL;
	if (*str == '[')
	{
		validate_json_read_array(str, count);
		str++;
		if (!(array = malloc(sizeof(t_json) * *count)))
			malloc_error();
		i = 0;
		while (*str && *str != ']')
			if ((r = parse_array_helper(&str, array, &i)) == -1)
				break ;
			else if (!r)
				return (0);
		str++;
		*source = str;
		*data = array;
		return (1);
	}
	return (0);
}

void	parse_object_state_2_helper_1(char **str, t_json *json, int count)
{
	char *tmp;

	tmp = *str;
	*str = validate_json_read_string(*str);
	json->data[count].type = 2;
	json->data[count].value = ft_strnew(*str - tmp);
	ft_strncpy(json->data[count].value, tmp, *str - tmp);
}
