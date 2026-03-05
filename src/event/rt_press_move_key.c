/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_press_move_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	rt_press_move_key(int keycode, t_key_state *keys)
{
	if (keycode == KEY_W)
		keys->w = 1;
	else if (keycode == KEY_S)
		keys->s = 1;
	else if (keycode == KEY_A)
		keys->a = 1;
	else if (keycode == KEY_D)
		keys->d = 1;
	else if (keycode == KEY_SPACE)
		keys->space = 1;
	else if (keycode == KEY_LEFT_CTRL)
		keys->left_ctrl = 1;
}
