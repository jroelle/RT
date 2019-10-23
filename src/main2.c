/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 19:28:12 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_env(t_env *env)
{
	env->ui_active = 0;
	env->read_scene = 0;
	env->space = 0;
	env->mouse = 0;
	env->canvas.update = 0;
	env->state = 1;
	env->start_render = 0;
	env->update_progressbar = 1;
	env->width = SCENE_WIDTH;
	env->height = SCENE_HEIGHT;
	env->need_clear = 1;
	env->ui_rerender = 0;
	env->in_render = 0;
	env->depth = 0;
	env->ready = 0;
	env->assets = NULL;
	env->assets_size = 0;
	env->texture_list = NULL;
	env->texture_index = 0;
	if (!(env->scene = malloc(sizeof(t_scene))))
		malloc_error();
	env->scene->objects = NULL;
	init_env_next(env);
}

void			main_cycle(t_env *env)
{
	SDL_Event	*event;
	int			i;

	if (!(event = (SDL_Event *)malloc(sizeof(SDL_Event))))
		malloc_error();
	env->state = 1;
	i = 0;
	while (env->state)
	{
		while (SDL_PollEvent(event))
		{
			if ((int)event->window.windowID == env->canvas.id)
				canvas_events_handler(env, event);
			else if ((int)event->window.windowID == env->ui.id)
				ui_events_handler(env, event);
		}
		if (env->ui.redraw)
			ui_redraw(env);
		canvas_render(env);
	}
}

void			console_mode(t_env *env, char *filename)
{
	env->canvas.scene = ft_strdup(filename);
	env->read_scene = 1;
	env->canvas_ready = 1;
}

int				main(int argc, char **argv)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_error();
	init_env(env);
	env->canvas_thread = SDL_CreateThread(canvas_render_thread,
		"canvas_render_thread", (void *)env);
	env->process_thread = SDL_CreateThread(process_thread,
		"process_thread", (void *)env);
	if (!sdl_init())
		return (1);
	canvas_init(&env->canvas);
	init_gpu(env);
	if (argc == 1)
		ui_mode(env);
	else if (argc == 2)
		console_mode(env, argv[1]);
	main_cycle(env);
	SDL_WaitThread(env->canvas_thread, NULL);
	SDL_WaitThread(env->process_thread, NULL);
	return (0);
}

void			error_exit(void)
{
	ft_putendl("SDL_Init Error");
	exit(1);
}
