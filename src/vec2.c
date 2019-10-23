/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:57:10 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 12:25:10 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		vec3_kdot(t_vec3 v1, t_vec3 v2, double k)
{
	double	d;

	d = vec3_dot(v1, v2) * k;
	if (d <= 0.0)
		return (0.0);
	if (d >= 1.0)
		return (1.0);
	return (d);
}

t_vec3		vec3_vec_mul(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x));
}

t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3_init(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x));
}

int			is_zero(t_vec3 v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}
