/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:54 by ross              #+#    #+#             */
/*   Updated: 2019/06/25 19:28:59 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				get_value_helper_2(char **tmp, char **str, t_json *json)
{
	int i;

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

int				get_value_helper(char **str, char **tmp, t_json *json)
{
	int r;

	if (**str == '.')
	{
		json = get_json_key(json, *tmp, *str - *tmp);
		if (!json)
			return (0);
		(*str)++;
		*tmp = *str;
	}
	else if (**str == '[')
		if (*tmp != *str)
		{
			if (!(r = get_value_helper_1(tmp, str, json)))
				return (0);
		}
		else
		{
			if (!(r = get_value_helper_2(tmp, str, json)))
				return (0);
		}
	else
		(*str)++;
	return (1);
}

char			*get_json_value(t_json *json, char *str)
{
	char	*tmp;
	int		r;

	tmp = str;
	while (str && *str)
	{
		if (!(r = get_value_helper(&str, &tmp, json)))
			return (NULL);
	}
	if (tmp != str)
		json = get_json_key(json, tmp, str - tmp);
	if (!json)
		return (NULL);
	if (json->type == 1 || json->type == 2)
		return (json->value);
	else
		return (NULL);
}

int				read_scene_helper(int fd, char **line, int *size)
{
	int		rd;
	char	buf[BUFSIZE];
	char	*tmp;

	if ((rd = read(fd, buf, BUFSIZE)) < 0)
		scene_error_exit("Error. Can't read file!\n");
	else if (!rd)
		return (0);
	else
	{
		if (*size == 0)
		{
			*line = ft_strnew(rd);
			*line = ft_strncat(*line, buf, rd);
			*size = rd;
		}
		else
		{
			tmp = ft_memjoin(*line, *size, buf, rd);
			free(*line);
			*line = tmp;
			*size += rd;
		}
	}
	return (1);
}

t_json			*read_json_scene(const char *filename)
{
	int		fd;
	char	*line;
	int		size;
	int		r;
	t_json	*json;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("Error. Can't open file!");
		exit(1);
	}
	size = 0;
	while (1)
		if (!(r = read_scene_helper(fd, &line, &size)))
			break ;
	if (!validate_json_read_object(line))
		scene_error_exit("Error: Invalid file format!\n");
	json = parse_json(line);
	if (!json)
		scene_error_exit("Error: parse!\n");
	return (json);
}
