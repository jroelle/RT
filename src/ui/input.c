/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:56:30 by gkessler          #+#    #+#             */
/*   Updated: 2019/06/23 16:01:52 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include <unistd.h>

void		malloc_error(void)
{
	write(1, "malloc error !!!\n", 17);
	exit(1);
}

void		input_edit_remove(t_input *input)
{
	input->content.label[strlen(input->content.label) - 1] = 0;
	input_destroy(input);
	input_init(input);
}

void		input_edit_add(t_input *input, char c)
{
	char		*str;
	int			len;

	str = NULL;
	len = strlen(input->content.label) + 2;
	if ((str = (char *)malloc(sizeof(char) * len)))
	{
		strcpy(str, input->content.label);
		str[len - 1] = 0;
		str[len - 2] = c;
		free(input->content.label);
		input->content.label = str;
		input_destroy(input);
		input_init(input);
	}
	else
		malloc_error();
}

int			input_edit(t_input *input, SDL_Keycode c)
{
	if (c >= 32 && c <= 126)
	{
		input_edit_add(input, (char)c);
		return (1);
	}
	else if (c == SDLK_BACKSPACE && strlen(input->content.label))
	{
		input_edit_remove(input);
		return (1);
	}
	return (0);
}

void		input_destroy(t_input *input)
{
	SDL_DestroyTexture(input->content.texture);
	SDL_FreeSurface(input->content.surface);
}
