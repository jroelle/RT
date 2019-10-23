/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:16:08 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/23 17:04:44 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_layouts_init(t_env *env)
{
	env->ui.layouts_count = 1;
	if (!(env->ui.layouts =
		(t_layout **)malloc(sizeof(t_layout *) * env->ui.layouts_count)))
		malloc_error();
	env->ui.layouts[0] = local_layout(env);
	env->ui.layouts[0]->id = 0;
	env->ui.layout = env->ui.layouts[0];
	env->ui.clear = 0;
}
