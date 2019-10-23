/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:37:33 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:21:03 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			canvas_render(t_env *env)
{
	if (env->canvas.update)
	{
		SDL_UpdateWindowSurface(env->canvas.window);
		env->canvas.update = 0;
	}
}

void			canvas_events_handler(t_env *env, SDL_Event *event)
{
	if (event->type == SDL_WINDOWEVENT &&
		event->window.event == SDL_WINDOWEVENT_CLOSE)
	{
		env->state = 0;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		event_keydown1(env, event);
		event_keydown2(env, event);
	}
	else if (event->type == SDL_MOUSEMOTION
		&& env->mouse && env->space)
	{
		env->scene->sample = 1;
		env->need_clear = 1;
		env->scene->camera.rotation =
		vec3_add_vec3(env->scene->camera.rotation,
		vec3_init(event->motion.yrel, event->motion.xrel, 0));
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		env->mouse = 1;
	else if (event->type == SDL_MOUSEBUTTONUP)
		env->mouse = 0;
}

void			event_keydown_move_w_s(t_env *env, SDL_Event *event)
{
	double x;
	double y;
	double z;

	env->need_clear = 1;
	y = (SCENE_WIDTH / 120.0) *
	sin(-env->scene->camera.rotation.x * M_PI / 180.0);
	z = (SCENE_WIDTH / 120.0) *
	cos(-env->scene->camera.rotation.x * M_PI / 180.0);
	x = z * (-sin(-env->scene->camera.rotation.y * M_PI / 180.0));
	z = z * cos(-env->scene->camera.rotation.y * M_PI / 180.0);
	env->scene->camera.position.x +=
	event->key.keysym.sym == SDLK_w ? x : -x;
	env->scene->camera.position.y +=
	event->key.keysym.sym == SDLK_w ? y : -y;
	env->scene->camera.position.z +=
	event->key.keysym.sym == SDLK_w ? z : -z;
	env->scene->sample = 1;
}

void			event_keydown1(t_env *env, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		env->state = 0;
	}
	if (event->key.keysym.sym == SDLK_TAB)
		env->scene->filter = (env->scene->filter + 1) % 5;
	if (event->key.keysym.sym == SDLK_SPACE)
	{
		if (!env->space && (env->space = 1))
			SDL_ShowCursor(SDL_DISABLE);
		else
		{
			env->space = 0;
			SDL_ShowCursor(SDL_ENABLE);
		}
	}
	if (event->key.keysym.sym == SDLK_F6)
		save_image(env);
	if (event->key.keysym.sym == SDLK_c && env->scene->filter == 4)
		env->scene->hue += 60;
}

void			event_keydown2(t_env *env, SDL_Event *event)
{
	double x;
	double z;

	if (env->space && (event->key.keysym.sym == SDLK_w ||
		event->key.keysym.sym == SDLK_s))
		event_keydown_move_w_s(env, event);
	if (env->space && (event->key.keysym.sym == SDLK_a ||
		event->key.keysym.sym == SDLK_d))
	{
		env->need_clear = 1;
		x = (SCENE_WIDTH / 120.0) *
			cos(-env->scene->camera.rotation.y * M_PI / 180.0);
		z = (SCENE_WIDTH / 120.0) *
			sin(-env->scene->camera.rotation.y * M_PI / 180.0);
		env->scene->camera.position.x +=
		event->key.keysym.sym == SDLK_d ? x : -x;
		env->scene->camera.position.z +=
		event->key.keysym.sym == SDLK_d ? z : -z;
		env->scene->sample = 1;
	}
}
