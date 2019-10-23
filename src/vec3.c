/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:57:10 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 12:25:37 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		vec2_length(t_vec2 v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double		vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec2		vec2_normalize(t_vec2 v)
{
	double	length;

	length = vec2_length(v);
	v.x /= length;
	v.y /= length;
	return (v);
}

t_vec3		vec3_normalize(t_vec3 v)
{
	return (vec3_div_n(v, vec3_length(v)));
}

double		vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}
