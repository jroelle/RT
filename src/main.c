/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/25 19:27:41 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*screenshot_name(void)
{
	char	*file;
	char	*t;
	int		n;

	file = ft_strdup("screenshots/image_0.ppm");
	n = 1;
	while (!access(file, 0))
	{
		free(file);
		file = ft_strjoin("screenshots/image_", ft_itoa(n));
		t = file;
		file = ft_strjoin(file, ".ppm");
		n++;
		free(t);
	}
	return (file);
}

void			save_image_next(t_env *env, int fd)
{
	Uint8	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < SCENE_HEIGHT)
	{
		j = 0;
		while (j < SCENE_WIDTH)
		{
			p = (Uint8 *)env->canvas.surface->pixels +
				i * env->canvas.surface->pitch +
				j * env->canvas.surface->format->BytesPerPixel;
			ft_putnbr_fd(p[2], fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(p[1], fd);
			ft_putstr_fd(" ", fd);
			ft_putnbr_fd(p[0], fd);
			ft_putstr_fd("\n", fd);
			j++;
		}
		i++;
	}
}

void			save_image(t_env *env)
{
	int		fd;
	char	*file;

	file = screenshot_name();
	fd = open(file, O_WRONLY | O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putstr_fd("P3\n", fd);
	ft_putnbr_fd(SCENE_WIDTH, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(SCENE_HEIGHT, fd);
	ft_putstr_fd("\n255\n", fd);
	save_image_next(env, fd);
	close(fd);
	free(file);
}

void			init_env_next(t_env *env)
{
	int i;

	init2(env);
	env->free_scene = 0;
	env->scene->depth = DEPTH;
	env->scene->noise = noise_array();
	if (!(env->scene->seeds = (t_seeds *)malloc(sizeof(t_seeds))))
		malloc_error();
	env->scene->seeds->size = (uint)(SCENE_HEIGHT * SCENE_WIDTH * 2);
	if (!(env->scene->seeds->seeds = (uint *)malloc(sizeof(uint) *
		env->scene->seeds->size)))
		malloc_error();
	if (!(env->scene->color_buffer = (t_vec3 *)malloc(sizeof(t_vec3) *
		SCENE_HEIGHT * SCENE_WIDTH)))
		malloc_error();
	if (!(env->color_buffers = malloc(sizeof(t_vec3 *) * 4)))
		malloc_error();
	i = -1;
	while (++i < 4)
		if (!(env->color_buffers[i] = malloc(sizeof(t_vec3)
		* SCENE_HEIGHT * SCENE_WIDTH)))
			malloc_error();
	env->process_state = -1;
}

void			init2(t_env *env)
{
	env->canvas_ready = 0;
	env->scene->count = 0;
	env->scene->models_count = 0;
	env->scene->models = NULL;
	env->scene->sample = 1;
	env->scene->filter = 0;
	env->scene->hue = 0;
}
