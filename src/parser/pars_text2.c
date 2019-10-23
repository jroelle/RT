/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_text2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:47:34 by drestles          #+#    #+#             */
/*   Updated: 2019/06/23 16:13:26 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_texture_list		*create_texture(char *name, SDL_Surface *image,
int texture_index)
{
	t_texture_list		*node;

	node = NULL;
	if ((node = (t_texture_list *)malloc(sizeof(t_texture_list))))
	{
		node->name = name;
		node->image = image;
		node->width = image->w;
		node->height = image->h;
		node->index = texture_index;
	}
	else
		malloc_error();
	return (node);
}

t_texture_list		*create_procedural_texture(int texture_index)
{
	t_texture_list	*node;

	node = NULL;
	if ((node = (t_texture_list *)malloc(sizeof(t_texture_list))))
	{
		node->name = ft_strdup("perlin");
		node->image = NULL;
		node->width = OCTAVES + 1;
		node->height = OCTAVES + 1;
		node->index = texture_index;
	}
	else
		malloc_error();
	return (node);
}

void				add_texture(t_texture_list **head, t_texture_list *node)
{
	t_texture_list *tmp;

	tmp = *head;
	*head = node;
	node->next = tmp;
}
