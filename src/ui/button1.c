/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:43:13 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/26 14:43:15 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

int		button_under_mouse(t_button *button, int x, int y)
{
	int dx;
	int dy;

	dx = x - button->view.position.x;
	dy = y - button->view.position.y;
	return (dx >= 0 && dy >= 0 && dx < button->view.size.width &&
			dy < button->view.size.height);
}

void	button_event_mousemotion(t_button *button,
			SDL_Event *event, int *result)
{
	if (button->state.hover != button_under_mouse(button,
		event->motion.x, event->motion.y))
	{
		button->state.hover = !button->state.hover;
		button->state.active = button->state.hover &&
			button->state.focus;
		*result = 1;
	}
}

void	button_event_mousedown(t_button *button, int *result)
{
	if (button->state.hover)
	{
		button->state.focus = 1;
		button->state.active = 1;
		*result = 1;
	}
	else
	{
		if (button->state.focus)
		{
			button->state.focus = 0;
		}
	}
}

void	button_event_mouseup(t_button *button, int *result)
{
	if (button->state.hover)
	{
		if (button->click.function && button->state.focus)
			button->click.function(button->click.argument);
		button->state.focus = 0;
		button->state.active = 0;
		*result = 1;
	}
	else
	{
		if (button->state.focus)
		{
			button->state.focus = 0;
		}
	}
}

int		button_event(t_button *button, SDL_Event *event)
{
	int result;

	result = 0;
	if (button->state.disabled)
		return (0);
	if (event->type == SDL_MOUSEMOTION)
		button_event_mousemotion(button, event, &result);
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		button_event_mousedown(button, &result);
	else if (event->type == SDL_MOUSEBUTTONUP)
		button_event_mouseup(button, &result);
	return (result);
}
