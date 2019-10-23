/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:58:43 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:27:02 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_cl_assets(t_env *env, t_cl *cl)
{
	if (!(cl->assets = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE, sizeof(t_vec3) * env->assets_size,
		NULL, NULL)))
		error_finish("gpu error: clCreateBuffer assets");
	if ((cl->err = clEnqueueWriteBuffer(cl->commands, cl->assets,
		CL_FALSE, 0, sizeof(t_vec3) * env->assets_size,
		env->assets, 0, 0, 0)) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueWriteBuffer assets");
}

void			init_gpu_after_read_scene(t_env *env)
{
	t_cl *cl;

	cl = env->cl;
	if (cl->objects)
		free(cl->objects);
	if (cl->models)
		free(cl->models);
	if (cl->assets)
		free(cl->assets);
	cl->objects = NULL;
	cl->models = NULL;
	cl->assets = NULL;
	if (env->scene->count)
		set_cl_objects(env, cl);
	if (env->scene->models_count)
		set_cl_models(env, cl);
	if (env->assets_size)
		set_cl_assets(env, cl);
}

int				set_gpu_args(t_env *env, t_cl *cl)
{
	int err;

	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->output);
	err |= clSetKernelArg(cl->kernel, 1, sizeof(int), &env->width);
	err |= clSetKernelArg(cl->kernel, 2, sizeof(int), &env->height);
	err |= clSetKernelArg(cl->kernel, 3, sizeof(int), &env->scene->count);
	err |= clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->objects);
	err |= clSetKernelArg(cl->kernel, 5, sizeof(int),
		&env->scene->models_count);
	err |= clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->models);
	err |= clSetKernelArg(cl->kernel, 7, sizeof(cl_mem), &cl->seed_gpu);
	err |= clSetKernelArg(cl->kernel, 8, sizeof(int), &env->scene->depth);
	err |= clSetKernelArg(cl->kernel, 9, sizeof(t_camera),
		&env->scene->camera);
	err |= clSetKernelArg(cl->kernel, 10, sizeof(cl_mem), &cl->assets);
	return (err);
}

void			render_gpu_next(t_env *env, t_cl *cl)
{
	int error;

	if ((cl->global = SCENE_WIDTH * SCENE_HEIGHT) % cl->local)
		error_finish("gpu error: global size must be multiple");
	if (clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
			&cl->global, &cl->local, 0, NULL, NULL) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueNDRangeKernel error");
	clFinish(cl->commands);
	if ((error = clEnqueueReadBuffer(cl->commands, cl->output, CL_TRUE, 0,
			SCENE_WIDTH * SCENE_HEIGHT * sizeof(t_vec3),
			env->gpu_calculations, 0, NULL, NULL)) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueReadBuffer error");
}

void			render_gpu(t_env *env)
{
	t_cl *cl;

	cl = env->cl;
	seeds_init(env);
	if ((cl->err = clEnqueueWriteBuffer(cl->commands, cl->seed_gpu,
			CL_FALSE, 0, sizeof(UINT) * env->scene->seeds->size,
			env->scene->seeds->seeds, 0, 0, 0)) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueWriteBuffer error");
	if (set_gpu_args(env, cl) != CL_SUCCESS)
		error_finish("gpu error: clSetKernelArg error\n");
	if (clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
				CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local),
				&cl->local, NULL) != CL_SUCCESS)
		error_finish("gpu error: clGetKernelWorkGroupInfo error\n");
	render_gpu_next(env, cl);
}
