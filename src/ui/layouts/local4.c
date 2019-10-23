/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 15:15:27 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			btn_median(t_env *env, t_button *button)
{
	f_position(&button->view.position, 10, 170);
	f_size(&button->view.size, UI_1W5, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "MEDIAN", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_median, (void *)env, 0);
}

void			btn_sepia(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_2C5, 170);
	f_size(&button->view.size, UI_1W5, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "SEPIA", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_sepia, (void *)env, 0);
}

void			btn_black_and_white(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_3C5, 170);
	f_size(&button->view.size, UI_1W5, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "B/W", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_black_and_white, (void *)env, 0);
}

void			btn_hue(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_4C5, 170);
	f_size(&button->view.size, UI_1W5, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "HUE", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_hue, (void *)env, 0);
}

void			btn_norm(t_env *env, t_button *button)
{
	f_position(&button->view.position, UI_5C5, 170);
	f_size(&button->view.size, UI_1W5, 30);
	f_view(&button->view, f_color(0, 0, 50));
	f_content(&button->content, "NORMAL", env->ui.font, f_color(255, 255, 255));
	f_button(button, env->ui.renderer);
	f_action(&button->click, click_norm, (void *)env, 0);
}
