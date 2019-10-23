/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:47:06 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_object_state_2_helper_2(char **str, t_json *json, int count)
{
	char *tmp;

	tmp = *str;
	*str = validate_json_read_number(*str);
	json->data[count].type = 1;
	json->data[count].value = ft_strnew(*str - tmp);
	ft_strncpy(json->data[count].value, tmp, *str - tmp);
}

int		parse_object_state_2(int *state, t_json *json, char **str, int count)
{
	t_json	*ptr;

	*state = 3;
	json->data[count].size = 0;
	if (**str == '"')
		parse_object_state_2_helper_1(str, json, count);
	else if ((**str == '-') || (**str >= '0' && **str <= '9'))
		parse_object_state_2_helper_2(str, json, count);
	else if (**str == '[')
	{
		json->data[count].type = 3;
		if (!json_parse_array(str, &json->data[count].data,
			&json->data[count].size))
			return (0);
	}
	else if (**str == '{')
	{
		ptr = &json->data[count];
		if (!json_parse_object(str, &ptr))
			return (0);
	}
	else
		return (-1);
	return (1);
}

void	parse_object_state_0_helper(int *state, t_json *json,
			char **str, int count)
{
	char *tmp;

	tmp = *str;
	*str = validate_json_read_string(*str);
	json->data[count].key = ft_strnew(*str - tmp - 2);
	ft_strncpy(json->data[count].key, tmp + 1, *str - tmp - 2);
	*state = 1;
}

int		parse_object_helper(char **str, int *state, t_json *json, int *count)
{
	int r;

	if (!*str || **str == '}')
		return (-1);
	if (*state == 0)
		parse_object_state_0_helper(state, json, str, *count);
	else if (*state == 1)
	{
		validate_json_state(state, 2, **str == ':');
		(*str)++;
	}
	else if (*state == 2)
	{
		if ((r = parse_object_state_2(state, json, str, *count)) == -1)
			return (-1);
		else if (!r)
			return (0);
	}
	else if (*state == 3)
	{
		validate_json_state(state, 0, **str == ',');
		(*count)++;
		(*str)++;
	}
	return (1);
}

void	parse_object_init(int *count, t_json *json, int *state, char **str)
{
	*count = get_keys_count(*str);
	json->data = (NULL);
	if (!(json->data = malloc(sizeof(t_json) * *count)))
		malloc_error();
	json->size = *count;
	json->type = 0;
	*state = 0;
	*count = 0;
	(*str)++;
}
