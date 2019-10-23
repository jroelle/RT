/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:51:28 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/26 14:51:30 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

Uint8		color_value_modify(Uint8 color, float value)
{
	return (color * value > 255 ? 255 : color * value);
}

unsigned	color_modify(unsigned color_initial, float value)
{
	t_color color;

	color.value = color_initial;
	color.sdl.a = 255;
	color.sdl.r = color_value_modify(color.sdl.r, value);
	color.sdl.g = color_value_modify(color.sdl.g, value);
	color.sdl.b = color_value_modify(color.sdl.b, value);
	return (color.value);
}
