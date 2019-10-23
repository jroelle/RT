/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:46:20 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/25 19:29:21 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_key_vec(t_vec3 *value, t_json *json, char *key, t_vec3 def)
{
	json = get_json_by_key(json, key);
	if (json)
	{
		if (json->size != 3)
		{
			ft_putendl("Incorrect %s vector");
			scene_error_exit("Must be 3 numbers\n");
		}
		*value = vec3_init(
			ft_atof(json->data[0].value),
			ft_atof(json->data[1].value),
			ft_atof(json->data[2].value));
	}
	else
		*value = def;
}

void	scene_key_double(double *value, t_json *json, char *key, double def)
{
	key = get_json_value(json, key);
	if (key)
		*value = ft_atof(key);
	else
		*value = def;
}

void	scene_key_int(int *value, t_json *json, char *key, int def)
{
	key = get_json_value(json, key);
	if (key)
		*value = (int)ft_atof(key);
	else
		*value = def;
}
