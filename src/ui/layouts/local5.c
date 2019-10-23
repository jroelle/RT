/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 19:15:37 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			click_stop(void *param)
{
	t_env *env;

	env = (t_env *)param;
	env->read_scene = 0;
	env->canvas_ready = 0;
	env->scene->sample = 1;
	env->process_state = -1;
	env->free_scene = 1;
	button_change_label(&(env->ui.layout->buttons[0]),
		ft_strdup("Nothing doing"));
	button_enabled(&(env->ui.layout->buttons[1]));
	button_disabled(&(env->ui.layout->buttons[2]));
	button_disabled(&(env->ui.layout->buttons[3]));
}

void			btn_stop(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_4C4, 90);
	f_size(&button->view.size, UI_1W4, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "STOP", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_stop, (void *)env, 0);
	button->state.disabled = 1;
}

t_layout		*local_layout(t_env *env)
{
	int			i;
	t_layout	*layout;

	layout = f_layout(11, 1);
	i = 0;
	btn_log(env, &(layout->buttons[0]));
	btn_render(env, &(layout->buttons[1]));
	btn_pause(env, &(layout->buttons[2]));
	btn_resume(env, &(layout->buttons[3]));
	btn_stop(env, &(layout->buttons[4]));
	btn_export(env, &(layout->buttons[5]));
	btn_median(env, &(layout->buttons[6]));
	btn_sepia(env, &(layout->buttons[7]));
	btn_black_and_white(env, &(layout->buttons[8]));
	btn_hue(env, &(layout->buttons[9]));
	btn_norm(env, &(layout->buttons[10]));
	inp_path(env, &(layout->inputs[0]));
	i = -1;
	while (++i < layout->buttons_count)
		button_init(&(layout->buttons[i]));
	i = -1;
	while (++i < layout->inputs_count)
		input_init(&(layout->inputs[i]));
	return (layout);
}
