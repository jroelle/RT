/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:37:33 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 18:36:52 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			put_pixel(t_env *env, int i)
{
	unsigned int	c;
	t_vec3			color;

	color = env->scene->color_buffer[i];
	color = vec3_div_n(color, env->scene->sample);
	if (env->scene->filter == 1)
		color = median(env->scene->color_buffer, i, env->scene->sample);
	else if (env->scene->filter == 2)
		color = sepia(color);
	else if (env->scene->filter == 3)
		color = black_white(color);
	else if (env->scene->filter == 4)
		color = hue(color, env->scene->hue);
	color.x = color.x > 1.0 ? 1.0 : color.x;
	color.y = color.y > 1.0 ? 1.0 : color.y;
	color.z = color.z > 1.0 ? 1.0 : color.z;
	color = vec3_mul_n(color, 255.0);
	c = SDL_MapRGBA(env->canvas.surface->format,
		color.x, color.y, color.z, 255);
	((unsigned int *)env->canvas.surface->pixels)[i] = c;
}
