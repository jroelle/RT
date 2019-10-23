/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:47:59 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/26 14:48:00 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		f_content(t_content *content,
	char *label, TTF_Font *font, unsigned color)
{
	content->label = strdup(label);
	content->view.color.initial = color;
	content->view.color.hover = color_hover(color);
	content->view.color.focus = color_focus(color);
	content->view.color.active = color_active(color);
	content->view.color.disabled = color_disabled();
	content->font = font;
}

void		f_action(t_action *action, void (*function)
	(void *), void *argument, int index)
{
	action->function = function;
	action->argument = argument;
	action->index = index;
}

void		f_position(t_position *position, int x, int y)
{
	position->x = x;
	position->y = y;
}

void		f_size(t_size *size, int width, int height)
{
	size->width = width;
	size->height = height;
}

void		f_view(t_view *view, unsigned color)
{
	view->color.initial = color;
	view->color.hover = color_hover(color);
	view->color.focus = color_focus(color);
	view->color.active = color_active(color);
	view->color.disabled = color_disabled();
}
