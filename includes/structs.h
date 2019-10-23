/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:15:32 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 20:40:05 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <OpenCL/opencl.h>

# define DEPTH 5

# include <string.h>

/*
** NET SECTION
*/
# define SERVER_INPUT 3456
# define SERVER_OUTPUT 6543
# define CLIENT_INPUT 4567
# define CLIENT_OUTPUT 7654
# define PACKET_SIZE 1024

# define UINT unsigned int

/*
** OPENCL SECTION
*/

typedef struct	s_cl
{
	int					err;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				output;
	cl_mem				objects;
	cl_mem				models;
	cl_mem				seed_gpu;
	cl_mem				logfile;
	cl_mem				assets;
	size_t				local;
	size_t				global;
}				t_cl;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef	struct	s_range
{
	double	min;
	double	max;
}				t_range;

typedef struct	s_hit
{
	int			index;
	double		distance;
	t_vec3		normal;
	t_vec3		point;
}				t_hit;

typedef struct	s_ray
{
	t_vec3		position;
	t_vec3		direction;
}				t_ray;

typedef struct	s_texture
{
	double		scale;
	int			index;
	unsigned	position;
	unsigned	width;
	unsigned	height;
	int			dx;
	int			dy;
}				t_texture;

typedef struct	s_texture_list
{
	SDL_Surface				*image;
	char					*name;
	int						index;
	int						width;
	int						height;
	struct s_texture_list	*next;
}				t_texture_list;

typedef struct	s_object
{
	int			type;
	int			active;
	t_vec3		position;
	t_vec3		odirection;
	t_vec3		direction;
	double		angle;
	double		radius;
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	int			model_index;
	double		minor_radius;
	double		major_radius;
	double		opacity;
	t_vec3		surface;
	int			boolean;
	int			proc_tex;
	int			wave;
	t_texture	texture;
	t_texture	map;
	t_texture	transparency;
}				t_object;

typedef struct	s_model
{
	double		specular;
	double		reflective;
	double		light;
	double		refractive_index;
	t_vec3		color;
	t_vec3		rotation;
	t_vec3		position;
	int			clip;
	int			active;
}				t_model;

typedef struct	s_viewport
{
	double		width;
	double		height;
	double		distance;
	t_vec2		delta;
}				t_viewport;

typedef struct	s_camera
{
	t_vec3		position;
	t_vec3		rotation;
	t_viewport	viewport;
	t_vec3		ambience;
}				t_camera;

typedef struct	s_seeds
{
	uint		*seeds;
	size_t		size;
}				t_seeds;

typedef struct	s_uint2
{
	unsigned int x;
	unsigned int y;
}				t_uint2;

typedef struct	s_scene
{
	int				depth;
	int				count;
	t_object		*objects;
	int				models_count;
	t_model			*models;
	t_camera		camera;
	int				render;
	int				sample;
	int				r_sample;
	t_vec3			*color_buffer;
	t_vec3			*radiance_cache;
	t_seeds			*seeds;
	int				filter;
	double			hue;
	t_vec2			**noise;
}				t_scene;

typedef struct	s_canvas
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	int			id;
	int			update;
	char		*scene;
}				t_canvas;

typedef struct	s_env
{
	t_cl			*cl;
	t_vec3			*gpu_calculations;
	int				width;
	int				height;
	int				ready;
	int				need_clear;
	int				state;
	t_scene			*scene;
	t_vec3			*assets;
	unsigned int	assets_size;
	int				start_render;
	int				camera_count_points;
	int				light_count_points;
	t_vec3			camera_path_points[DEPTH];
	t_vec3			light_path_points[DEPTH + 1];
	t_texture_list	*texture_list;
	int				texture_index;
	int				depth;
	int				ui_rerender;
	int				in_render;
	int				update_progressbar;
	SDL_Thread		*ping_thread;
	SDL_Thread		*listen_thread;
	SDL_Thread		*controle_thread;
	t_ui			ui;
	t_canvas		canvas;
	int				ui_active;
	int				read_scene;
	int				canvas_ready;
	int				space;
	int				mouse;
	t_vec3			**color_buffers;
	int				process_state;
	int				btn_arg;
	int				free_scene;
	SDL_Thread		*ui_thread;
	SDL_Thread		*canvas_thread;
	SDL_Thread		*process_thread;
	SDL_Thread		*netprocess_thread;
}				t_env;

typedef union	u_random
{
	float			f;
	unsigned int	ui;
}				t_random;

#endif
