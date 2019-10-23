/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 13:40:56 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

unsigned	f_color(int r, int g, int b)
{
	t_color color;

	color.sdl.r = r;
	color.sdl.g = g;
	color.sdl.b = b;
	color.sdl.a = 255;
	return (color.value);
}

unsigned	color_hover(unsigned color_initial)
{
	return (color_modify(color_initial, 1.5));
}

unsigned	color_focus(unsigned color_initial)
{
	return (color_modify(color_initial, 2));
}

unsigned	color_active(unsigned color_initial)
{
	return (color_modify(color_initial, 2));
}

unsigned	color_disabled(void)
{
	t_color color;

	color.sdl.a = 255;
	color.sdl.r = 128;
	color.sdl.g = 128;
	color.sdl.b = 128;
	return (color.value);
}
