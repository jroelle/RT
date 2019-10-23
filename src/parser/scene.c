/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:36:59 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:48:50 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	read_scene_objects(t_env *env, t_json *json_objects, int i, int *c)
{
	int			j;
	t_json		*json;
	t_object	*obj;
	t_scene		*scene;

	scene = env->scene;
	j = 0;
	while (j < json_objects->size)
	{
		json = &json_objects->data[j];
		obj = &scene->objects[*c];
		obj->model_index = i;
		scene_key_int(&obj->type, json, "type", -1);
		scene_key_int(&obj->active, json, "active", 1);
		obj->active *= scene->models[i].active;
		scene_key_vec(&obj->position, json, "position", vec3_init(0, 0, 0));
		obj->position = vec3_add_vec3(obj->position, scene->models[i].position);
		scene_key_vec(&obj->odirection, json, "direction", vec3_init(0, 0, 0));
		read_scene_objects_next(scene, json, i, obj);
		read_scene_objects_next_next(json, env, obj);
		*c += 1;
		j++;
	}
}

void	read_scene_models(t_env *env, t_json *json_models)
{
	int		i;
	int		c;
	t_json	*json;
	t_json	*json_objects;
	t_model	*m;

	i = -1;
	c = 0;
	while (++i < env->scene->models_count)
	{
		m = &env->scene->models[i];
		json = &json_models->data[i];
		scene_key_int(&m->active, json, "active", 1);
		scene_key_vec(&m->color, json, "color", vec3_init(1, 1, 1));
		scene_key_vec(&m->rotation, json, "rotation", vec3_init(0, 0, 0));
		scene_key_vec(&m->position, json, "position", vec3_init(0, 0, 0));
		scene_key_double(&m->specular, json, "specular", 0);
		scene_key_double(&m->reflective, json, "reflective", 0);
		scene_key_double(&m->light, json, "light", 0);
		scene_key_double(&m->refractive_index, json, "refractive_index", 1);
		m->clip = 0;
		json_objects = get_json_by_key(json, "objects");
		read_scene_objects(env, json_objects, i, &c);
	}
}

void	read_scene_from_json_next(t_env *env, t_json *json)
{
	t_json	*json_models;
	t_json	*json_objects;
	t_scene	*scene;
	int		i;

	scene = env->scene;
	json_models = get_json_by_key(json, "models");
	if (json_models)
		env->scene->models_count = json_models->size;
	i = -1;
	while (++i < scene->models_count)
	{
		json_objects = get_json_by_key(&json_models->data[i], "objects");
		if (!json_objects)
			scene_error_exit("Error parse objects\n");
		scene->count += json_objects->size;
	}
	if (!(scene->objects = (t_object *)malloc(sizeof(t_object) * scene->count)))
		malloc_error();
	if (!(scene->models = (t_model *)malloc(sizeof(t_model)
		* scene->models_count)))
		malloc_error();
	read_scene_models(env, json_models);
}

void	read_scene_from_json(t_env *env)
{
	t_json	*json;
	t_json	*json_camera;
	t_scene	*scene;

	scene = env->scene;
	if (!(json = read_json_scene(env->canvas.scene)))
		scene_error_exit("Error parse file\n");
	read_scene_from_json_next(env, json);
	json_camera = get_json_by_key(json, "camera");
	scene_key_vec(&scene->camera.position, json_camera,
		"position", vec3_init(0, 0, 0));
	scene_key_vec(&scene->camera.rotation, json_camera,
		"rotation", vec3_init(0, 0, 0));
	scene_key_vec(&scene->camera.ambience, json_camera,
		"ambience", vec3_init(0, 0, 0));
	textrure_combine(env);
}

void	scene_init(t_env *env)
{
	t_scene	*scene;
	int		i;

	scene = env->scene;
	scene->camera.viewport.height = 1;
	scene->camera.viewport.width = (double)SCENE_WIDTH / (double)SCENE_HEIGHT *
		scene->camera.viewport.height;
	scene->camera.viewport.distance = 1;
	scene->camera.viewport.delta.x = scene->camera.viewport.width /
		(double)SCENE_WIDTH;
	scene->camera.viewport.delta.y = scene->camera.viewport.height /
		(double)SCENE_HEIGHT;
	i = -1;
	while (++i < SCENE_HEIGHT * SCENE_WIDTH)
		scene->color_buffer[i] = vec3_init(0.0, 0.0, 0.0);
	read_scene_from_json(env);
	scene->render = 1;
}
