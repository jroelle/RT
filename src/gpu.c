/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <lbradama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:58:43 by lbradama          #+#    #+#             */
/*   Updated: 2019/06/25 19:25:51 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*ft_strjoin_spec(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*newstr;

	i = s1 ? ft_strlen(s1) : 0;
	j = s2 ? ft_strlen(s2) : 0;
	newstr = NULL;
	if (i + j)
		if ((newstr = (char *)malloc(sizeof(char) * (i + j + 1))))
		{
			if (s1)
				ft_strcpy(newstr, s1);
			if (s2)
				ft_strcpy(newstr + i, s2);
			newstr[i + j] = '\0';
		}
	return (newstr);
}

int				concat_files(char **str, char *filename)
{
	int		fd;
	char	buf[20000];
	int		rd;
	char	*newstr;

	ft_bzero(buf, 20000);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	rd = read(fd, buf, 20000);
	if (rd < 0)
		return (0);
	close(fd);
	newstr = ft_strjoin_spec(*str, buf);
	if (newstr)
	{
		free(*str);
		*str = newstr;
		return (1);
	}
	return (0);
}

int				read_cl(char **code)
{
	int state;

	state = 1;
	state = state & concat_files(code, "./src/gpu/_structs.cl");
	state = state & concat_files(code, "./src/gpu/_functions.cl");
	state = state & concat_files(code, "./src/gpu/random.cl");
	state = state & concat_files(code, "./src/gpu/vec3.cl");
	state = state & concat_files(code, "./src/gpu/range.cl");
	state = state & concat_files(code, "./src/gpu/ray.cl");
	state = state & concat_files(code, "./src/gpu/camera.cl");
	state = state & concat_files(code, "./src/gpu/transparency.cl");
	state = state & concat_files(code, "./src/gpu/intersect.cl");
	state = state & concat_files(code, "./src/gpu/solutions.cl");
	state = state & concat_files(code, "./src/gpu/normal.cl");
	state = state & concat_files(code, "./src/gpu/tools.cl");
	state = state & concat_files(code, "./src/gpu/texture.cl");
	state = state & concat_files(code, "./src/gpu/trace.cl");
	state = state & concat_files(code, "./src/gpu/procedural_texture.cl");
	state = state & concat_files(code, "./src/gpu/_kernel.cl");
	return (state);
}

void			error_finish(char *str)
{
	ft_putendl(str);
	exit(1);
}

void			build_error(t_cl *cl)
{
	free(cl);
	ft_putendl("GPU build error");
	error_finish("gpu error: clBuildProgram error");
}
