/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:58:43 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:27:32 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_gpu_linux(t_cl *cl)
{
	cl_platform_id		platforms[100];
	cl_uint				platforms_n;
	cl_uint				devices_n;

	platforms_n = (cl_uint)0;
	devices_n = (cl_uint)0;
	clGetPlatformIDs(100, platforms, &platforms_n);
	if ((cl->err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1,
		&cl->device_id, &devices_n)) != CL_SUCCESS)
		if ((cl->err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU,
			100, &cl->device_id, &devices_n)) != CL_SUCCESS)
			error_finish("HOLY SHIT!!!\n");
	cl->context = clCreateContext(NULL, 1, &cl->device_id,
		NULL, NULL, &cl->err);
}

void			init_gpu_next(t_env *env, t_cl *cl, char *kernel_source)
{
	if (!(cl->commands = clCreateCommandQueue(cl->context,
			cl->device_id, 0, &cl->err)))
		error_finish("gpu error: clCreateCommandQueue error");
	if (!read_cl(&kernel_source))
		error_finish("gpu error: read_cl error");
	if (!(cl->program = clCreateProgramWithSource(cl->context,
			1, (const char **)&kernel_source, NULL, &cl->err)))
		error_finish("gpu error: clCreateProgramWithSource error");
	if ((cl->err = clBuildProgram(cl->program, 0, NULL,
		"-I includes", NULL, NULL)) != CL_SUCCESS)
		build_error(cl);
	cl->kernel = clCreateKernel(cl->program, "processed", &cl->err);
	if (!cl->kernel || cl->err != CL_SUCCESS)
		error_finish("gpu error: clCreateKernel error\n");
	if (!(cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
		SCENE_WIDTH * SCENE_HEIGHT * sizeof(t_vec3), NULL, NULL)))
		error_finish("gpu error: clCreateBuffer error: cl->output\n");
	if (!(cl->seed_gpu = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * env->scene->seeds->size, NULL, NULL)))
		error_finish("gpu error: clCreateBuffer error: cl->seed_gpu\n");
	cl->objects = NULL;
	cl->models = NULL;
	cl->assets = NULL;
}

void			init_gpu(t_env *env)
{
	char *kernel_source;
	t_cl *cl;

	if (!(env->gpu_calculations = (t_vec3 *)malloc(sizeof(t_vec3) *
		SCENE_WIDTH * SCENE_HEIGHT)))
		malloc_error();
	if (!(env->cl = (t_cl *)malloc(sizeof(t_cl))))
		malloc_error();
	cl = env->cl;
	kernel_source = NULL;
	if ((cl->err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU,
		1, &cl->device_id, NULL)) != CL_SUCCESS)
		if ((cl->err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU,
			1, &cl->device_id, NULL)) != CL_SUCCESS)
			error_finish("gpu error: clGetDeviceIDs error");
	if (!(cl->context = clCreateContext(0, 1, &cl->device_id,
		NULL, NULL, &cl->err)))
		error_finish("gpu error: clCreateContext error");
	init_gpu_next(env, cl, kernel_source);
}

void			set_cl_objects(t_env *env, t_cl *cl)
{
	if (!(cl->objects = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE, sizeof(t_object) * env->scene->count,
		NULL, NULL)))
		error_finish("gpu error: clCreateBuffer objects");
	if ((cl->err = clEnqueueWriteBuffer(cl->commands,
		cl->objects, CL_FALSE, 0,
		sizeof(t_object) * env->scene->count,
		env->scene->objects, 0, 0, 0)) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueWriteBuffer objects");
}

void			set_cl_models(t_env *env, t_cl *cl)
{
	if (!(cl->models = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE, sizeof(t_model) *
		env->scene->models_count, NULL, NULL)))
		error_finish("gpu error: clCreateBuffer models");
	if ((cl->err = clEnqueueWriteBuffer(cl->commands, cl->models,
		CL_FALSE, 0, sizeof(t_model) * env->scene->models_count,
		env->scene->models, 0, 0, 0)) != CL_SUCCESS)
		error_finish("gpu error: clEnqueueWriteBuffer models");
}
