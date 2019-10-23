/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:42:47 by drestles          #+#    #+#             */
/*   Updated: 2019/06/23 16:12:54 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_texture_list	*check_texture_list(t_texture_list *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
			return (head);
		head = head->next;
	}
	return (head);
}

void			help(t_env *env, unsigned int *pos, Uint8 *pixel)
{
	env->assets[*pos].x = (float)pixel[2] / 255.0;
	env->assets[*pos].y = (float)pixel[1] / 255.0;
	env->assets[*pos].z = (float)pixel[0] / 255.0;
}

void			texture_rec_next(t_env *env,
t_texture_list *cur, unsigned int *pos)
{
	Uint8	*pixel;
	int		x;
	int		y;
	int		i;

	i = -1;
	if (cur->image)
		while (++i < cur->width * cur->height)
		{
			pixel = (Uint8 *)cur->image->pixels + i
			* cur->image->format->BytesPerPixel;
			help(env, pos, pixel);
			(*pos)++;
		}
	else
		while (++i < cur->width * cur->height)
		{
			x = i % cur->width;
			y = i / cur->height;
			env->assets[*pos].x = env->scene->noise[y][x].x;
			env->assets[*pos].y = env->scene->noise[y][x].y;
			env->assets[*pos].z = 0.0;
			(*pos)++;
		}
}

void			texture_rec(t_env *env, t_texture_list *cur, unsigned int *pos)
{
	int		i;

	i = -1;
	while (++i < env->scene->count)
	{
		if (env->scene->objects[i].texture.index == cur->index)
			env->scene->objects[i].texture.position = *pos;
		if (env->scene->objects[i].map.index == cur->index)
			env->scene->objects[i].map.position = *pos;
		if (env->scene->objects[i].transparency.index == cur->index)
			env->scene->objects[i].transparency.position = *pos;
	}
	texture_rec_next(env, cur, pos);
}

void			textrure_combine(t_env *env)
{
	unsigned int	pos;
	t_texture_list	*cur;

	if (env->texture_list)
	{
		pos = 0;
		cur = env->texture_list;
		while (cur)
		{
			pos += cur->width * cur->height;
			cur = cur->next;
		}
		if (!(env->assets = malloc(sizeof(t_vec3) * pos)))
			malloc_error();
		env->assets_size = pos;
		cur = env->texture_list;
		pos = 0;
		while (cur)
		{
			texture_rec(env, cur, &pos);
			cur = cur->next;
		}
	}
}
