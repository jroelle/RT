/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 19:15:58 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			click_render(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->canvas.scene = ft_strdup(env->ui.layout->inputs[0].content.label);
	env->read_scene = 1;
	env->canvas_ready = 1;
	env->scene->filter = 0;
	button_enabled(&(env->ui.layout->buttons[2]));
	button_disabled(&(env->ui.layout->buttons[3]));
	button_disabled(&(env->ui.layout->buttons[1]));
}

void			click_pause(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->canvas_ready = 0;
	button_disabled(&(env->ui.layout->buttons[2]));
	button_enabled(&(env->ui.layout->buttons[3]));
}

void			click_resume(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->canvas_ready = 1;
	button_enabled(&(env->ui.layout->buttons[2]));
	button_disabled(&(env->ui.layout->buttons[3]));
}

void			click_export(void *param)
{
	t_env *env;

	env = (t_env *)param;
	save_image(env);
}

void			click_median(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->scene->filter = 1;
}
