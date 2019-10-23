/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:35:02 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/21 14:24:35 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			hue(t_vec3 color, double hue)
{
	t_vec3 hsv;

	hsv = rgb_to_hsv(color);
	hsv.x += hue;
	while (hsv.x >= 360.0)
		hsv.x -= 360;
	return (hsv_to_rgb(hsv));
}

t_vec3			sepia(t_vec3 color)
{
	t_vec3 rgb;

	rgb = color;
	rgb.x = color.x * 0.393 + color.y * 0.769 + color.z * 0.189;
	rgb.y = color.x * 0.349 + color.y * 0.686 + color.z * 0.168;
	rgb.z = color.x * 0.272 + color.y * 0.534 + color.z * 0.131;
	return (rgb);
}

t_vec3			black_white(t_vec3 color)
{
	t_vec3 hsv;

	hsv = rgb_to_hsv(color);
	hsv.y = 0;
	return (hsv_to_rgb(hsv));
}
