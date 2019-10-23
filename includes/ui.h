/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:02:05 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/23 16:27:11 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <SDL2/SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>

# define UI_WIDTH 600
# define UI_HEIGHT 240

# define UI_1W1 (UI_WIDTH - 20)
# define UI_1W2 (UI_WIDTH - 30) / 2
# define UI_1W3 (UI_WIDTH - 40) / 3
# define UI_1W4 (UI_WIDTH - 50) / 4
# define UI_1W5 (UI_WIDTH - 60) / 5

# define UI_2W3 2 * (UI_WIDTH - 40) / 3 + 10
# define UI_3W4 3 * (UI_WIDTH - 50) / 4 + 20
# define UI_2W5 2 * (UI_WIDTH - 60) / 5 + 10
# define UI_3W5 3 * (UI_WIDTH - 60) / 5 + 20

# define UI_1C1 10

# define UI_1C2 10
# define UI_2C2 20 + (UI_WIDTH - 30) / 2

# define UI_1C3 10
# define UI_2C3 20 + (UI_WIDTH - 40) / 3
# define UI_3C3 30 + 2 * (UI_WIDTH - 40) / 3

# define UI_1C4 10
# define UI_2C4 20 + (UI_WIDTH - 50) / 4
# define UI_3C4 30 + 2 * (UI_WIDTH - 50) / 4
# define UI_4C4 40 + 3 * (UI_WIDTH - 50) / 4

# define UI_1C5 10
# define UI_2C5 20 + (UI_WIDTH - 60) / 5
# define UI_3C5 30 + 2 * (UI_WIDTH - 60) / 5
# define UI_4C5 40 + 3 * (UI_WIDTH - 60) / 5
# define UI_5C5 50 + 4 * (UI_WIDTH - 60) / 5

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef union	u_color
{
	unsigned	value;
	SDL_Color	sdl;
}				t_color;

typedef struct	s_state_color
{
	unsigned initial;
	unsigned hover;
	unsigned focus;
	unsigned active;
	unsigned disabled;
}				t_state_color;

typedef struct	s_state
{
	int hover;
	int focus;
	int disabled;
	int active;

	int redraw;
}				t_state;

typedef struct	s_position
{
	int x;
	int y;
}				t_position;

typedef struct	s_size
{
	int width;
	int height;
}				t_size;

typedef	struct	s_view
{
	t_position		position;
	t_size			size;
	t_state_color	color;
	SDL_Rect		sdl_rect;
}				t_view;

typedef struct	s_content
{
	char		*label;
	t_view		view;
	TTF_Font	*font;
	SDL_Surface	*surface;
	SDL_Texture	*texture;
}				t_content;

typedef struct	s_action
{
	void	(*function)(void *);
	void	*argument;
	int		index;
}				t_action;

typedef struct	s_button
{
	t_view			view;
	t_content		content;
	t_state			state;
	t_action		click;
	SDL_Renderer	*renderer;
}				t_button;

typedef struct	s_input
{
	t_view			view;
	t_content		content;
	t_state			state;
	t_action		click;
	SDL_Renderer	*renderer;
}				t_input;

typedef struct	s_layout
{
	int			id;
	TTF_Font	*font;
	t_button	*buttons;
	int			buttons_count;
	t_input		*inputs;
	int			inputs_count;
}				t_layout;

typedef struct	s_ui
{
	int				id;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	t_layout		**layouts;
	int				layouts_count;
	t_layout		*layout;
	int				clear;
	int				redraw;
}				t_ui;

/*
** structs
*/
unsigned		f_color(int r, int g, int b);
void			f_position(t_position *position, int x, int y);
void			f_size(t_size *size, int width, int height);
void			f_view(t_view *view, unsigned color);
void			f_content(t_content *content, char *label, TTF_Font *font,
				unsigned color);
void			f_action(t_action *action, void (*function)(void *),
				void *argument, int index);
unsigned		color_modify(unsigned color_initial, float value);
unsigned		color_hover(unsigned color_initial);
unsigned		color_focus(unsigned color_initial);
unsigned		color_active(unsigned color_initial);
unsigned		color_disabled(void);

/*
** button
*/
void			f_button(t_button *button, SDL_Renderer *renderer);
void			button_init(t_button *button);
void			button_change_label(t_button *button, char *new_label);
void			button_draw(t_button *button);
void			button_destroy(t_button *button);
int				button_event(t_button *button, SDL_Event *event);
void			button_disabled(t_button *button);
void			button_enabled(t_button *button);

/*
** input
*/
void			f_input(t_input *input, SDL_Renderer *renderer);
void			input_init(t_input *input);
void			input_draw(t_input *input, int immediately);
void			input_destroy(t_input *input);
int				input_event(t_input *input, SDL_Event *event);

/*
** layout
*/
t_layout		*f_layout(int buttons_count, int inputs_count);
void			layout_draw(t_layout *layout, SDL_Renderer *renderer);
void			layout_destroy(t_layout *layout);
int				layout_event(t_layout *layout, SDL_Event *event);
int				input_edit(t_input *input, SDL_Keycode c);

/*
** general
*/
int				sdl_init();
int				ui_init(t_ui *ui);
void			ui_destroy(t_ui *ui);
void			clear_screen(SDL_Renderer *renderer);
void			sdl_destroy();
void			malloc_error(void);

#endif
