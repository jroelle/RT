/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_progress_bar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 10:37:33 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 16:52:38 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			update_progressbar(t_env *env)
{
	char	*pre;
	char	*num;
	char	*tmp;
	char	*res;
	int		count;

	count = 1 + env->scene->sample / 100;
	count = count > 100 ? 100 : count;
	if (!(tmp = malloc(sizeof(char) * 12)))
		malloc_error();
	tmp[11] = 0;
	tmp[10] = ' ';
	ft_memset(tmp, '_', 10);
	ft_memset(tmp, '#', count);
	pre = ft_strjoin("rendering ( ", tmp);
	free(tmp);
	num = ft_itoa(env->scene->sample < 1000 ? env->scene->sample / 10 : 100);
	tmp = ft_strjoin(pre, num);
	free(num);
	free(pre);
	res = ft_strjoin(tmp, "%)");
	free(tmp);
	button_change_label(&(env->ui.layout->buttons[0]), res);
	env->ui.redraw = 1;
}
