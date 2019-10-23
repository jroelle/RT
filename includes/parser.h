/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestles <drestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:20:30 by ross              #+#    #+#             */
/*   Updated: 2019/05/19 16:15:00 by drestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>

# define BUFSIZE 1024

typedef struct	s_json
{
	int				type;
	struct s_json	*data;
	int				size;
	char			*key;
	char			*value;
}				t_json;

#endif
