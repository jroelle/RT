/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 11:02:06 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:29:25 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ui_mode(t_env *env)
{
	ui_init(&env->ui);
	ui_layouts_init(env);
	env->ui_active = 1;
	env->ui.redraw = 1;
	env->ui.clear = 1;
	SDL_SetWindowPosition(env->ui.window, 1000, 100);
	SDL_RaiseWindow(env->canvas.window);
	SDL_RaiseWindow(env->ui.window);
}

void			ui_redraw(t_env *env)
{
	env->ui.redraw = 0;
	clear_screen(env->ui.renderer);
	layout_draw(env->ui.layout, env->ui.renderer);
}

void			ui_events_handler(t_env *env, SDL_Event *event)
{
	if (event->type == SDL_WINDOWEVENT &&
	event->window.event == SDL_WINDOWEVENT_CLOSE)
	{
		env->state = 0;
		return ;
	}
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
	{
		env->state = 0;
	}
	if (env->ui_active)
		if (layout_event(env->ui.layout, event))
			env->ui.redraw = 1;
}
