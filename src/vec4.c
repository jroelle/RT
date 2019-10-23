/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:57:10 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 12:27:53 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3		vec3_add_n(t_vec3 v, double n)
{
	v.x += n;
	v.y += n;
	v.z += n;
	return (v);
}

t_vec3		vec3_add_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec2		vec2_sub_vec2(t_vec2 v1, t_vec2 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return (v1);
}

t_vec3		vec3_sub_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec3		vec3_mul_vec3(t_vec3 v1, t_vec3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}
