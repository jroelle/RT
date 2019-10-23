/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:37:33 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:36:42 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				canvas_init(t_canvas *canvas)
{
	canvas->window = SDL_CreateWindow("RT", 0, 0, SCENE_WIDTH, SCENE_HEIGHT, 0);
	canvas->surface = SDL_GetWindowSurface(canvas->window);
	canvas->id = SDL_GetWindowID(canvas->window);
	return (0);
}

int				process_thread(void *param)
{
	t_env *env;

	env = (t_env *)param;
	while (env->state)
	{
		if (!env->process_state)
		{
			env->process_state = 1;
			render_gpu(env);
			if (env->process_state == 1)
			{
				if (env->ui_active)
					update_progressbar(env);
				env->process_state = 2;
			}
		}
	}
	return (0);
}

void			canvas_render_thread_next(t_env *env, t_vec3 *buff)
{
	int i;

	i = 0;
	while (i < SCENE_HEIGHT * SCENE_WIDTH)
	{
		env->scene->color_buffer[i] = vec3_add_vec3(
			env->scene->color_buffer[i], buff[i]);
		put_pixel(env, i);
		i++;
	}
	env->scene->sample++;
	env->canvas.update = 1;
	if (env->process_state == 2)
		env->process_state = 0;
}

void			canvas_render_thread_help(t_env *env)
{
	int		i;

	if (env->need_clear)
	{
		env->need_clear = 0;
		env->scene->sample = 1;
		ft_memset(env->scene->color_buffer, 0,
			sizeof(t_vec3) * SCENE_WIDTH * SCENE_HEIGHT);
		i = -1;
		env->process_state = 0;
		while (++i < SCENE_HEIGHT * SCENE_WIDTH)
			put_pixel(env, i);
	}
	if (env->read_scene)
	{
		scene_init(env);
		init_gpu_after_read_scene(env);
		if (env->ui_active)
			button_enabled(&(env->ui.layout->buttons[4]));
		env->read_scene = 0;
		env->need_clear = 1;
		env->process_state = 0;
	}
}

int				canvas_render_thread(void *param)
{
	t_env		*env;
	t_vec3		*buff;

	env = (t_env *)param;
	while (env->state)
	{
		if (env->free_scene)
			free_scene(env);
		if (env->canvas_ready && !env->canvas.update)
		{
			canvas_render_thread_help(env);
			buff = NULL;
			if (env->process_state == 2)
				buff = env->gpu_calculations;
			if (buff)
				canvas_render_thread_next(env, buff);
		}
	}
	return (0);
}
