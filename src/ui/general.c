/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 19:37:19 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include <unistd.h>

int			sdl_init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		write(1, "SDL_Init Error\n", 15);
		return (0);
	}
	if (TTF_Init() == -1)
	{
		write(1, "TTF_Init Error\n", 15);
		return (0);
	}
	return (1);
}

int			ui_init(t_ui *ui)
{
	if ((ui->window = SDL_CreateWindow("RT", 0, 0,
		UI_WIDTH, UI_HEIGHT, 0)) == NULL)
	{
		write(1, "SDL_CreateWindow Error\n", 23);
		return (0);
	}
	if ((ui->renderer = SDL_CreateRenderer(ui->window, -1, 0)) == NULL)
	{
		write(1, "SDL_CreateRenderer Error\n", 25);
		return (0);
	}
	ui->id = SDL_GetWindowID(ui->window);
	ui->font = TTF_OpenFont("fonts/test.otf", 16);
	SDL_RenderSetLogicalSize(ui->renderer, UI_WIDTH, UI_HEIGHT);
	ui->redraw = 1;
	return (1);
}

void		ui_destroy(t_ui *ui)
{
	layout_destroy(ui->layout);
	TTF_CloseFont(ui->font);
	SDL_DestroyRenderer(ui->renderer);
	SDL_DestroyWindow(ui->window);
}

void		sdl_destroy(void)
{
	TTF_Quit();
	SDL_Quit();
}

void		clear_screen(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
