/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 18:49:15 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			json_parse_object(char **source, t_json **json_mem)
{
	t_json	*json;
	char	*str;
	int		count;
	int		state;
	int		r;

	json = *json_mem;
	str = *source;
	if (*str == '{')
	{
		parse_object_init(&count, json, &state, &str);
		while (*str && *str != '}')
		{
			str = validate_json_skip_empty(str);
			if ((r = parse_object_helper(&str,
				&state, json, &count)) == -1)
				break ;
			else if (!r)
				return (0);
		}
		str++;
		*source = str;
		return (1);
	}
	return (0);
}

t_json		*parse_json(char *str)
{
	t_json *json;

	if (!(json = malloc(sizeof(t_json))))
		return (NULL);
	if (!json_parse_object(&str, &json))
		return (NULL);
	return (json);
}

t_json		*get_json_key(t_json *json, char *str, int n)
{
	int i;

	if (json->type == 0)
	{
		i = -1;
		while (++i < json->size)
			if (!ft_strncmp(json->data[i].key, str, n))
				return (&json->data[i]);
		return (NULL);
	}
	return (NULL);
}

t_json		*get_json_by_key(t_json *json, char *str)
{
	int i;

	if (json->type == 0)
	{
		i = -1;
		while (++i < json->size)
			if (!ft_strcmp(json->data[i].key, str))
				return (&json->data[i]);
		return (NULL);
	}
	return (NULL);
}

int			get_value_helper_1(char **tmp, char **str, t_json *json)
{
	int i;

	json = get_json_key(json, *tmp, *str - *tmp);
	if (!json)
		return (0);
	(*str)++;
	i = ft_atoi(*str);
	if (json->type != 3 || json->size <= i)
		return (0);
	json = &json->data[i];
	while (**str >= '0' && **str <= '9')
		(*str)++;
	(*str)++;
	*tmp = *str;
	return (1);
}
