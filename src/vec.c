/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:57:10 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 12:23:49 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec2		vec2_init(double x, double y)
{
	t_vec2 v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec3		vec3_init(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3		vec3_div_n(t_vec3 v, double n)
{
	v.x /= n;
	v.y /= n;
	v.z /= n;
	return (v);
}

t_vec3		vec3_mul_n(t_vec3 v, double n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}
