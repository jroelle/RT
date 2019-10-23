/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:35:02 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/21 14:23:21 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3			rgb_to_hsv(t_vec3 rgb)
{
	t_vec3	hsv;
	double	delta;
	double	cmax;
	double	cmin;

	cmax = MAX(rgb.x, MAX(rgb.y, rgb.z));
	cmin = MIN(rgb.x, MIN(rgb.y, rgb.z));
	delta = cmax - cmin;
	if (fabs(delta) < 0.000001)
		hsv.x = 0.0;
	else if (fabs(cmax - rgb.x) < 0.000001)
		hsv.x = 60.0 * ((int)((rgb.y - rgb.z) / delta) % 6);
	else if (fabs(cmax - rgb.y) < 0.000001)
		hsv.x = 60.0 * ((rgb.z - rgb.x) / delta + 2.0);
	else if (fabs(cmax - rgb.z) < 0.000001)
		hsv.x = 60.0 * ((rgb.x - rgb.y) / delta + 4.0);
	if (fabs(delta) < 0.000001)
		hsv.y = 0.0;
	else
		hsv.y = delta / (1.0 - fabs(cmax + cmin - 1));
	hsv.z = (cmax + cmin) / 2.0;
	return (hsv);
}

t_vec3			hsv_to_rgb(t_vec3 hsv)
{
	t_vec3 rgb;
	double c;
	double x;
	double m;

	c = (1.0 - fabs(2.0 * hsv.z - 1.0)) * hsv.y;
	x = c * (1.0 - fabs((int)(hsv.x / 60.0) % 2 - 1.0));
	m = hsv.z - c / 2.0;
	if (hsv.x >= 0.0 && hsv.x < 60.0)
		rgb = vec3_init(c, x, 0);
	else if (hsv.x >= 60.0 && hsv.x < 120.0)
		rgb = vec3_init(x, c, 0);
	else if (hsv.x >= 120.0 && hsv.x < 180.0)
		rgb = vec3_init(0, c, x);
	else if (hsv.x >= 180.0 && hsv.x < 240.0)
		rgb = vec3_init(0, x, c);
	else if (hsv.x >= 240.0 && hsv.x < 300.0)
		rgb = vec3_init(x, 0, c);
	else
		rgb = vec3_init(c, 0, x);
	rgb = vec3_add_n(rgb, m);
	return (rgb);
}

static	void	median_array(t_vec2 *median_window,
t_vec3 *color_buffer, int ind, int samples)
{
	int i;
	int x;
	int y;

	x = ind % SCENE_WIDTH - 2;
	y = ind / SCENE_WIDTH - 2;
	i = 0;
	while (i < 25)
	{
		if (x < 0 || x >= SCENE_WIDTH)
			x = x < 0 ? 0 : SCENE_WIDTH - 1;
		if (y < 0 || y >= SCENE_HEIGHT)
			y = y < 0 ? 0 : SCENE_HEIGHT - 1;
		median_window[i].x = rgb_to_hsv(vec3_div_n(
			color_buffer[y * SCENE_WIDTH + x], (double)samples)).z;
		median_window[i].y = y * SCENE_WIDTH + x;
		x++;
		if (x >= ind % SCENE_WIDTH + 3)
		{
			x = ind % SCENE_WIDTH - 2;
			y++;
		}
		i++;
	}
}

t_vec3			median(t_vec3 *color_buffer, int ind, int samples)
{
	int		i;
	int		j;
	t_vec2	median_window[25];
	t_vec2	t;

	median_array(median_window, color_buffer, ind, samples);
	i = 0;
	while (i < 24)
	{
		j = 0;
		while (j < 24 - i)
		{
			if (median_window[j].x > median_window[j + 1].x)
			{
				t = median_window[j];
				median_window[j] = median_window[j + 1];
				median_window[j + 1] = t;
			}
			j++;
		}
		i++;
	}
	t = median_window[12];
	return (vec3_div_n(color_buffer[(int)(t.y)], (double)samples));
}
