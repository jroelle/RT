/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroelle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:42:36 by jroelle           #+#    #+#             */
/*   Updated: 2019/06/26 14:42:38 by jroelle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void	button_disabled(t_button *button)
{
	button->state.disabled = 1;
	button->state.focus = 0;
	button->state.hover = 0;
	button->state.active = 0;
}

void	button_enabled(t_button *button)
{
	button->state.disabled = 0;
	button->state.focus = 0;
	button->state.hover = 0;
	button->state.active = 0;
}
