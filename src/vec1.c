/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:57:10 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 12:24:24 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		rot_x(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;

	res.x = v.x;
	res.y = v.y * cos(invert * rot.x) + v.z * -sin(invert * rot.x);
	res.z = v.y * sin(invert * rot.x) + v.z * cos(invert * rot.x);
	return (res);
}

t_vec3		rot_y(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;

	res.x = v.x * cos(invert * rot.y) + v.z * sin(invert * rot.y);
	res.y = v.y;
	res.z = v.x * -sin(invert * rot.y) + v.z * cos(invert * rot.y);
	return (res);
}

t_vec3		rot_z(t_vec3 v, t_vec3 rot, int invert)
{
	t_vec3 res;

	res.x = v.x * cos(invert * rot.z) + v.y * -sin(invert * rot.z);
	res.y = v.x * sin(invert * rot.z) + v.y * cos(invert * rot.z);
	res.z = v.z;
	return (res);
}

t_vec3		vec3_rotate(t_vec3 v, t_vec3 rot, int invert)
{
	v = rot_x(v, rot, invert);
	v = rot_y(v, rot, invert);
	v = rot_z(v, rot, invert);
	return (v);
}

double		vec3_distance(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v = vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
