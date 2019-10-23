/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:47:28 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/26 14:47:29 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

int			input_under_mouse(t_input *input, int x, int y)
{
	int dx;
	int dy;

	dx = x - input->view.position.x;
	dy = y - input->view.position.y;
	return (dx >= 0 && dy >= 0 && dx < input->view.size.width &&
			dy < input->view.size.height);
}

void		input_event_mousemotion(t_input *input, SDL_Event *event,
				int *result)
{
	if (input->state.hover != input_under_mouse(input,
		event->motion.x, event->motion.y))
	{
		input->state.hover = !input->state.hover;
		input->state.active = input->state.hover
			&& input->state.focus;
		input->state.redraw = 1;
		*result = (1);
	}
}

void		input_event_mousedown(t_input *input, int *result)
{
	if (input->state.hover)
	{
		input->state.focus = 1;
		input->state.active = 1;
		input->state.redraw = 1;
		*result = 1;
	}
	else
	{
		if (input->state.focus)
		{
			input->state.focus = 0;
			input->state.redraw = 1;
			*result = 1;
		}
	}
}

void		input_event_mouseup(t_input *input, int *result)
{
	if (input->state.hover)
	{
		if (input->click.function && input->state.focus)
			input->click.function(input->click.argument);
		input->state.active = 0;
		input->state.redraw = 1;
		*result = 1;
	}
	else
	{
		if (input->state.focus)
		{
			input->state.focus = 0;
			input->state.redraw = 1;
			*result = 1;
		}
	}
}

int			input_event(t_input *input, SDL_Event *event)
{
	int result;

	result = 0;
	if (event->type == SDL_MOUSEMOTION)
		input_event_mousemotion(input, event, &result);
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		input_event_mousedown(input, &result);
	else if (event->type == SDL_MOUSEBUTTONUP)
		input_event_mouseup(input, &result);
	else if (event->type == SDL_KEYDOWN)
	{
		if (input->state.focus)
		{
			if (input_edit(input, event->key.keysym.sym))
			{
				input->state.redraw = 1;
				result = 1;
			}
		}
	}
	return (result);
}
