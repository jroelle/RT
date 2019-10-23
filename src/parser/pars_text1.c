/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_text1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:47:34 by drestles          #+#    #+#             */
/*   Updated: 2019/06/25 19:28:42 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			scene_error_exit(char *error)
{
	ft_putendl(error);
	exit(1);
}

t_texture		load_texture(char *value, t_env *env, SDL_Surface *image)
{
	t_texture_list		*texture_cur;
	t_texture			result;

	texture_cur = create_texture(value + 1, image, env->texture_index);
	env->texture_index = env->texture_index + 1;
	if (texture_cur)
	{
		result.index = texture_cur->index;
		result.width = texture_cur->width;
		result.height = texture_cur->height;
		add_texture(&env->texture_list, texture_cur);
	}
	else
	{
		result.index = -1;
		result.width = 0;
		result.height = 0;
		scene_error_exit(value);
	}
	return (result);
}

t_texture		load_procedural_texture(t_env *env)
{
	t_texture_list		*texture_cur;
	t_texture			result;

	texture_cur = create_procedural_texture(env->texture_index);
	env->texture_index = env->texture_index + 1;
	if (texture_cur)
	{
		result.index = texture_cur->index;
		result.width = texture_cur->width;
		result.height = texture_cur->height;
		add_texture(&env->texture_list, texture_cur);
	}
	else
	{
		result.index = -1;
		result.width = 0;
		result.height = 0;
		scene_error_exit("load_procedural_texture\n");
	}
	return (result);
}

t_texture		get_object_texture(char *value, t_env *env)
{
	t_texture_list	*texture_cur;
	t_texture		result;
	SDL_Surface		*image;

	texture_cur = NULL;
	value[ft_strlen(value) - 1] = 0;
	texture_cur = check_texture_list(env->texture_list, value + 1);
	result.index = -1;
	if (texture_cur)
	{
		result.index = texture_cur->index;
		result.width = texture_cur->width;
		result.height = texture_cur->height;
	}
	else
	{
		image = IMG_Load(value + 1);
		if (image)
			return (load_texture(value, env, image));
		else
			scene_error_exit(value);
	}
	return (result);
}

t_texture		get_object_procedural_texture(t_env *env)
{
	t_texture_list		*texture_cur;
	t_texture			result;

	texture_cur = NULL;
	texture_cur = check_texture_list(env->texture_list, "perlin");
	result.index = -1;
	if (texture_cur)
	{
		result.index = texture_cur->index;
		result.width = texture_cur->width;
		result.height = texture_cur->height;
	}
	else
	{
		return (load_procedural_texture(env));
	}
	return (result);
}
