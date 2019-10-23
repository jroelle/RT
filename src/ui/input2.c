/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 13:38:12 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void		f_input(t_input *input, SDL_Renderer *renderer)
{
	input->state.disabled = 0;
	input->state.focus = 0;
	input->state.hover = 0;
	input->state.active = 0;
	input->state.redraw = 1;
	input->click.function = NULL;
	input->click.argument = NULL;
	input->renderer = renderer;
}

void		input_init(t_input *input)
{
	t_color color;

	color.value = input->content.view.color.initial;
	input->content.surface = TTF_RenderUTF8_Blended(input->content.font,
		input->content.label, color.sdl);
	input->content.texture = SDL_CreateTextureFromSurface(input->renderer,
		input->content.surface);
	SDL_QueryTexture(input->content.texture, NULL, NULL,
		&input->content.view.size.width, &input->content.view.size.height);
	if (!input->view.size.width)
		input->view.size.width = input->content.view.size.width;
	if (!input->view.size.height)
		input->view.size.height = input->content.view.size.height;
	input->view.sdl_rect.x = input->view.position.x;
	input->view.sdl_rect.y = input->view.position.y;
	input->view.sdl_rect.w = input->view.size.width;
	input->view.sdl_rect.h = input->view.size.height;
	input->content.view.position.x = input->view.position.x;
	input->content.view.position.y = input->view.position.y + (
		input->view.size.height - input->content.view.size.height) / 2;
	input->content.view.sdl_rect.x = input->content.view.position.x;
	input->content.view.sdl_rect.y = input->content.view.position.y;
	input->content.view.sdl_rect.w = input->content.view.size.width;
	input->content.view.sdl_rect.h = input->content.view.size.height;
}

void		input_draw(t_input *input, int immediately)
{
	t_color color;

	input->state.redraw = 0;
	color.value = input->view.color.initial;
	if (input->state.hover)
		color.value = input->view.color.hover;
	if (input->state.focus)
		color.value = input->view.color.focus;
	SDL_SetRenderDrawColor(input->renderer, color.sdl.r,
		color.sdl.g, color.sdl.b, color.sdl.a);
	SDL_RenderFillRect(input->renderer, &input->view.sdl_rect);
	SDL_RenderCopy(input->renderer, input->content.texture,
		NULL, &input->content.view.sdl_rect);
	if (immediately)
		SDL_RenderPresent(input->renderer);
}
