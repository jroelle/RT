/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:15:17 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/26 15:55:39 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <OpenCL/opencl.h>
# include <time.h>
# include <sys/time.h>
# include "ui.h"
# include "structs.h"
# include "libft.h"
# include "parser.h"

# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define MAGENTA			"\x1b[35m"
# define CYAN				"\x1b[36m"
# define RESET				"\x1b[0m"

# ifndef M_PI
#  define M_PI				3.14159265358979323846
# endif

# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))

# define SCENE_WIDTH		512
# define SCENE_HEIGHT		512

# define OCTAVES			16
# define CHESSBOARD			10
# define BRICKS				4

# define TEXTURE_WIDTH		512
# define TEXTURE_HEIGHT		512

# define RENDER_WINDOW_ID	1
# define UI_WINDOW_ID		2

# define GPU 1

int				ui_create(t_env *env);
t_vec3			podrandom(t_vec3 v, t_vec3 tangent_space_dir);

void			seeds_init(t_env *env);

t_vec2			vec2_init(double x, double y);
t_vec3			vec3_init(double x, double y, double z);
t_vec3			vec3_div_n(t_vec3 v, double n);
t_vec3			vec3_mul_n(t_vec3 v, double n);
t_vec3			vec3_add_n(t_vec3 v, double n);
t_vec3			vec3_add_vec3(t_vec3 v1, t_vec3 v2);
t_vec2			vec2_sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec3			vec3_sub_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mul_vec3(t_vec3 v1, t_vec3 v2);
double			vec2_length(t_vec2 v);
double			vec3_length(t_vec3 v);
t_vec2			vec2_normalize(t_vec2 v);
t_vec3			vec3_normalize(t_vec3 v);
double			vec2_dot(t_vec2 v1, t_vec2 v2);
double			vec3_dot(t_vec3 v1, t_vec3 v2);
double			vec3_kdot(t_vec3 v1, t_vec3 v2, double k);
t_vec3			vec3_vec_mul(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
int				is_zero(t_vec3 v);
t_vec3			rot_x(t_vec3 v, t_vec3 rot, int invert);
t_vec3			rot_y(t_vec3 v, t_vec3 rot, int invert);
t_vec3			rot_z(t_vec3 v, t_vec3 rot, int invert);
t_vec3			vec3_rotate(t_vec3 v, t_vec3 rot, int invert);
double			vec3_distance(t_vec3 v1, t_vec3 v2);

t_vec3			rgb_to_hsv(t_vec3 rgb);
t_vec3			hsv_to_rgb(t_vec3 hsv);
t_vec3			hue(t_vec3 color, double hue);
t_vec3			sepia(t_vec3 color);
t_vec3			black_white(t_vec3 color);
t_vec3			median(t_vec3 *color_buffer, int ind, int samples);

void			set_cl_models(t_env *env, t_cl *cl);
void			set_cl_objects(t_env *env, t_cl *cl);
void			init_gpu_next(t_env *env, t_cl *cl, char *kernel_source);
void			init_gpu_linux(t_cl *cl);
void			set_cl_assets(t_env *env, t_cl *cl);
void			render_gpu_next(t_env *env, t_cl *cl);
void			build_error(t_cl *cl);

void			put_pixel(t_env *env, int i);

void			scene_init(t_env *env);
t_vec3			hue(t_vec3 color, double hue);
void			init2(t_env *env);

t_vec2			**noise_array();

void			init_gpu(t_env *env);
void			render_gpu(t_env *env);
void			init_gpu_after_read_scene(t_env *env);
void			error_finish(char *str);
int				read_cl(char **code);

void			ui_layouts_init(t_env *env);
t_layout		*choose_layout(t_env *env);
t_layout		*local_layout(t_env *env);
t_layout		*remote_layout(t_env *env);

t_json			*read_json_scene(const char *filename);
t_json			*parse_json(char *str);
t_json			*get_json_by_key(t_json *json, char *str);
char			*get_json_value(t_json *json, char *str);
char			*validate_json_read_object(char *str);
int				validate_json_state(int *state, int new_state, int check);
char			*validate_json_skip_empty(char *str);
char			*validate_json_read_string(char *str);
char			*validate_json_read_number(char *str);
char			*validate_json_read_array(char *str, int *size);
char			*validate_json_read_object(char *str);
char			*validate_get_str(char *str);
int				validate_object_helper(char **str, int *state);
int				get_keys_count(char *str);
int				json_parse_array(char **source, t_json **data, int *count);
int				json_parse_object(char **source, t_json **json_mem);
void			parse_array_helper_1(char **str, t_json *array, int *i);
void			parse_object_state_2_helper_1(char **str, t_json *json,
					int count);
void			parse_object_state_2_helper_2(char **str, t_json *json,
					int count);
int				parse_object_helper(char **str, int *state, t_json *json,
					int *count);
void			parse_object_init(int *count, t_json *json, int *state,
					char **str);
t_json			*get_json_key(t_json *json, char *str, int n);
int				get_value_helper_1(char **tmp, char **str, t_json *json);

void			read_scene_objects_next(t_scene *scene, t_json *json, int i,
					t_object *obj);
void			read_scene_objects_next_next(t_json *json,
					t_env *env, t_object *obj);
void			scene_key_vec(t_vec3 *value,
					t_json *json, char *key, t_vec3 def);
void			scene_key_double(double *value,
					t_json *json, char *key, double def);
void			scene_key_int(int *value, t_json *json, char *key, int def);

t_texture_list	*create_texture(char *name, SDL_Surface *image,
					int texture_index);
t_texture_list	*create_procedural_texture(int texture_index);
void			add_texture(t_texture_list **head, t_texture_list *node);
t_texture_list	*check_texture_list(t_texture_list *head, char *name);
void			texture_rec(t_env *env, t_texture_list *cur, unsigned int *pos);
void			textrure_combine(t_env *env);

void			scene_error_exit(char *error);
t_texture		load_texture(char *value, t_env *env, SDL_Surface *image);
t_texture		get_object_texture(char *value, t_env *env);
t_texture		get_object_procedural_texture(t_env *env);

char			*screenshot_name(void);
void			save_image_next(t_env *env, int fd);
void			save_image(t_env *env);
void			error_exit(void);
void			init_env_next(t_env *env);
void			init_env(t_env *env);
void			main_cycle(t_env *env);
void			console_mode(t_env *env, char *filename);
int				main(int argc, char **argv);

int				canvas_init(t_canvas *canvas);
void			canvas_gpu(t_env *env);
int				canvas_render_thread(void *param);
int				process_thread(void *param);
void			canvas_render(t_env *env);
void			canvas_events_handler(t_env *env, SDL_Event *event);
void			event_keydown_move_w_s(t_env *env, SDL_Event *event);
void			event_keydown1(t_env *env, SDL_Event *event);
void			event_keydown2(t_env *env, SDL_Event *event);

void			ui_mode(t_env *env);
void			ui_redraw(t_env *env);
void			ui_events_handler(t_env *env, SDL_Event *event);
void			btn_export(t_env *env, t_button *button);
void			btn_log(t_env *env, t_button *button);
t_layout		*local_layout(t_env *env);
void			btn_render(t_env *env, t_button *button);
void			btn_pause(t_env *env, t_button *button);
void			inp_path(t_env *env, t_input *input);
void			malloc_error(void);

void			click_render(void *param);
void			click_pause(void *param);
void			click_resume(void *param);
void			click_export(void *param);
void			click_median(void *param);
void			click_sepia(void *param);
void			click_black_and_white(void *param);
void			click_hue(void *param);
void			click_norm(void *param);
void			inp_path(t_env *env, t_input *input);
void			btn_render(t_env *env, t_button *button);
void			btn_pause(t_env *env, t_button *button);
void			btn_resume(t_env *env, t_button *button);
void			btn_export(t_env *env, t_button *button);
void			btn_log(t_env *env, t_button *button);
void			btn_median(t_env *env, t_button *button);
void			btn_sepia(t_env *env, t_button *button);
void			btn_black_and_white(t_env *env, t_button *button);
void			btn_hue(t_env *env, t_button *button);
void			btn_norm(t_env *env, t_button *button);
t_layout		*local_layout(t_env *env);
void			update_progressbar(t_env *env);
void			free_scene(t_env *env);
int				button_event(t_button *button, SDL_Event *event);
void			button_disabled(t_button *button);
void			button_enabled(t_button *button);

#endif
