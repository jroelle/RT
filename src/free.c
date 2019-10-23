/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 20:40:31 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_scene(t_env *env)
{
	t_texture_list *node;
	t_texture_list *tmp;

	if (env->scene->objects)
		free(env->scene->objects);
	if (env->scene->models)
		free(env->scene->models);
	if (env->assets)
		free(env->assets);
	env->scene->objects = NULL;
	env->scene->models = NULL;
	env->assets = NULL;
	env->assets_size = 0;
	node = env->texture_list;
	while (node)
	{
		tmp = node->next;
		SDL_FreeSurface(node->image);
		free(node);
		node = tmp;
	}
	env->texture_list = NULL;
	env->free_scene = 0;
}
