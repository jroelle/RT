/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 16:33:40 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			click_sepia(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->scene->filter = 2;
}

void			click_black_and_white(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->scene->filter = 3;
}

void			click_hue(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->scene->filter = 4;
	env->scene->hue += 60;
}

void			click_norm(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->scene->filter = 0;
	env->scene->hue = 0;
}

void			inp_path(t_env *env, t_input *input)
{
	f_position(&input->view.position, UI_1C1, 50);
	f_size(&input->view.size, (UI_1W1), 30);
	f_view(&input->view, f_color(100, 100, 100));
	f_content(&input->content, "scenes/01.json",
		env->ui.font, f_color(0, 0, 0));
	f_input(input, env->ui.renderer);
}
