/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:46:14 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/23 10:46:15 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	read_scene_objects_next(t_scene *scene, t_json *json,
			int i, t_object *obj)
{
	obj->direction = vec3_rotate(obj->odirection,
		vec3_init(M_PI * scene->models[i].rotation.x / 180.0,
		M_PI * scene->models[i].rotation.y / 180.0,
		M_PI * scene->models[i].rotation.z / 180.0),
		1);
	scene_key_double(&obj->radius, json, "radius", 0);
	scene_key_int(&obj->boolean, json, "boolean", 1);
	if (obj->boolean == -1)
		scene->models[i].clip = 1;
	scene_key_double(&obj->minor_radius, json, "minor_radius", 0);
	scene_key_double(&obj->major_radius, json, "major_radius", 0);
	scene_key_double(&obj->opacity, json, "opacity", 1);
	scene_key_double(&obj->angle, json, "angle", 0);
	scene_key_vec(&obj->surface, json, "surface", vec3_init(0, 0, 0));
	scene_key_vec(&obj->a, json, "a", vec3_init(0, 0, 0));
	obj->a = vec3_add_vec3(obj->a, scene->models[i].position);
	scene_key_vec(&obj->b, json, "b", vec3_init(0, 0, 0));
	obj->b = vec3_add_vec3(obj->b, scene->models[i].position);
	scene_key_vec(&obj->c, json, "c", vec3_init(0, 0, 0));
	obj->c = vec3_add_vec3(obj->c, scene->models[i].position);
	scene_key_int(&obj->wave, json, "wave", 0);
}

void	read_texture(t_object *obj, t_env *env, t_json *json)
{
	char *value;

	obj->texture.index = -1;
	value = get_json_value(json, "texture");
	scene_key_int(&obj->proc_tex, json, "procedural_texture", 0);
	if (value || obj->proc_tex == 1)
	{
		if (obj->proc_tex == 1)
			obj->texture = get_object_procedural_texture(env);
		else
			obj->texture = get_object_texture(value, env);
	}
	scene_key_double(&obj->texture.scale, json, "tex_scale", 1);
	obj->texture.scale = obj->texture.scale < 0 ? 1 : obj->texture.scale;
	scene_key_int(&obj->texture.dx, json, "tex_dx", 0);
	scene_key_int(&obj->texture.dy, json, "tex_dy", 0);
}

void	read_map(t_object *obj, t_env *env, t_json *json)
{
	char *value;

	obj->map.index = -1;
	value = get_json_value(json, "map");
	if (value)
		obj->map = get_object_texture(value, env);
	scene_key_double(&obj->map.scale, json, "map_scale", 1);
	obj->map.scale = obj->map.scale < 0 ? 1 : obj->map.scale;
	scene_key_int(&obj->map.dx, json, "map_dx", 0);
	scene_key_int(&obj->map.dy, json, "map_dy", 0);
}

void	read_transparency(t_object *obj, t_env *env, t_json *json)
{
	char *value;

	obj->transparency.index = -1;
	value = get_json_value(json, "transparency");
	if (value)
		obj->transparency = get_object_texture(value, env);
	scene_key_double(&obj->transparency.scale, json, "transparency_scale", 1);
	obj->transparency.scale =
		obj->transparency.scale < 0 ? 1 : obj->transparency.scale;
	scene_key_int(&obj->transparency.dx, json, "transparency_dx", 0);
	scene_key_int(&obj->transparency.dy, json, "transparency_dy", 0);
}

void	read_scene_objects_next_next(t_json *json,
	t_env *env, t_object *obj)
{
	read_texture(obj, env, json);
	read_map(obj, env, json);
	read_transparency(obj, env, json);
}
