/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 15:51:45 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_layout		*f_layout(int buttons_count, int inputs_count)
{
	t_layout *layout;

	if (!(layout = malloc(sizeof(t_layout))))
		malloc_error();
	layout->buttons = NULL;
	layout->inputs = NULL;
	if ((layout->buttons_count = buttons_count))
		if (!(layout->buttons = (t_button *)malloc(
				sizeof(t_button) * buttons_count)))
			malloc_error();
	if ((layout->inputs_count = inputs_count))
		if (!(layout->inputs = (t_input *)malloc(
				sizeof(t_input) * inputs_count)))
			malloc_error();
	return (layout);
}

int				layout_event(t_layout *layout, SDL_Event *event)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while (i < layout->buttons_count)
	{
		if (button_event(&(layout->buttons[i]), event))
			result = 1;
		i++;
	}
	i = 0;
	while (i < layout->inputs_count)
	{
		if (input_event(&(layout->inputs[i]), event))
			result = 1;
		i++;
	}
	return (result);
}

void			layout_draw(t_layout *layout, SDL_Renderer *renderer)
{
	int i;

	i = 0;
	while (i < layout->buttons_count)
		button_draw(&(layout->buttons[i++]));
	i = 0;
	while (i < layout->inputs_count)
		input_draw(&(layout->inputs[i++]), 0);
	SDL_RenderPresent(renderer);
}

void			layout_destroy(t_layout *layout)
{
	int i;

	i = 0;
	while (i < layout->buttons_count)
		button_destroy(&(layout->buttons[i++]));
	i = 0;
	while (i < layout->inputs_count)
		input_destroy(&(layout->inputs[i++]));
}
