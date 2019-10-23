/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkessler <gkessler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:45 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/23 15:49:14 by gkessler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec2			**noise_array(void)
{
	t_vec2		**n;
	int			i;
	int			j;
	double		angle;

	if (!(n = (t_vec2 **)malloc(sizeof(t_vec2 *) * (OCTAVES + 1))))
		malloc_error();
	i = 0;
	while (i < OCTAVES + 1)
	{
		if (!(n[i] = (t_vec2 *)malloc(sizeof(t_vec2) * (OCTAVES + 1))))
			malloc_error();
		j = 0;
		while (j < OCTAVES + 1)
		{
			angle = drand48() * 2.0 * M_PI;
			n[i][j].x = cos(angle);
			n[i][j].y = sin(angle);
			j++;
		}
		i++;
	}
	return (n);
}
