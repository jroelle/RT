/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 15:59:02 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	f_button(t_button *button, SDL_Renderer *renderer)
{
	button->state.disabled = 0;
	button->state.focus = 0;
	button->state.hover = 0;
	button->state.active = 0;
	button->state.redraw = 0;
	button->click.function = NULL;
	button->click.argument = NULL;
	button->renderer = renderer;
}

void	button_init(t_button *button)
{
	t_color color;

	color.value = button->content.view.color.initial;
	button->content.surface = TTF_RenderUTF8_Blended(button->content.font,
		button->content.label, color.sdl);
	button->content.texture = SDL_CreateTextureFromSurface(button->renderer,
		button->content.surface);
	SDL_QueryTexture(button->content.texture, NULL, NULL, &button->content.
		view.size.width, &button->content.view.size.height);
	if (!button->view.size.width)
		button->view.size.width = button->content.view.size.width;
	if (!button->view.size.height)
		button->view.size.height = button->content.view.size.height;
	button->view.sdl_rect.x = button->view.position.x;
	button->view.sdl_rect.y = button->view.position.y;
	button->view.sdl_rect.w = button->view.size.width;
	button->view.sdl_rect.h = button->view.size.height;
	button->content.view.position.x = button->view.position.x + (button->
		view.size.width - button->content.view.size.width) / 2;
	button->content.view.position.y = button->view.position.y + (button->
		view.size.height - button->content.view.size.height) / 2;
	button->content.view.sdl_rect.x = button->content.view.position.x;
	button->content.view.sdl_rect.y = button->content.view.position.y;
	button->content.view.sdl_rect.w = button->content.view.size.width;
	button->content.view.sdl_rect.h = button->content.view.size.height;
}

void	button_change_label(t_button *button, char *new_label)
{
	char		*old_label;
	SDL_Surface	*old_surface;
	SDL_Texture	*old_texture;

	old_surface = button->content.surface;
	old_texture = button->content.texture;
	old_label = button->content.label;
	button->content.label = new_label;
	button_init(button);
	free(old_label);
	SDL_DestroyTexture(old_texture);
	SDL_FreeSurface(old_surface);
}

void	button_draw(t_button *button)
{
	t_color color;

	if (button->state.redraw)
	{
		free(button->content.surface);
		free(button->content.texture);
		button_init(button);
		button->state.redraw = 0;
	}
	color.value = button->view.color.initial;
	if (button->state.hover)
		color.value = button->view.color.hover;
	if (button->state.active)
		color.value = button->view.color.active;
	if (button->state.disabled)
		color.value = button->view.color.disabled;
	SDL_SetRenderDrawColor(button->renderer, color.sdl.r, color.sdl.g,
		color.sdl.b, color.sdl.a);
	SDL_RenderFillRect(button->renderer, &button->view.sdl_rect);
	SDL_RenderCopy(button->renderer, button->content.texture, NULL,
		&button->content.view.sdl_rect);
}

void	button_destroy(t_button *button)
{
	SDL_DestroyTexture(button->content.texture);
	SDL_FreeSurface(button->content.surface);
}
