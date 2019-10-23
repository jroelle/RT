/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/24 18:55:26 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			btn_render(t_env *env, t_button *button)
{
	f_position(&button->view.position, 10, 90);
	f_size(&button->view.size, UI_1W4, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "RENDER", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_render, (void *)env, 0);
}

void			btn_pause(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_2C4, 90);
	f_size(&button->view.size, UI_1W4, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "PAUSE", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_pause, (void *)env, 0);
	button->state.disabled = 1;
}

void			btn_resume(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_3C4, 90);
	f_size(&button->view.size, UI_1W4, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "RESUME", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_resume, (void *)env, 0);
	button->state.disabled = 1;
}

void			btn_export(t_env *env, t_button *button)
{
	f_position(&button->view.position, 10, 130);
	f_size(&button->view.size, 580, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "EXPORT", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_export, (void *)env, 0);
}

void			btn_log(t_env *env, t_button *button)
{
	f_position(&button->view.position, 10, 10);
	f_size(&button->view.size, 580, 30);
	f_view(&button->view, f_color(0, 0, 0));
	f_content(&button->content, "Nothing doing",
		env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
}
