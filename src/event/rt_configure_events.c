/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_configure_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	void	rt_initialize_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.space = 0;
	data->keys.left_ctrl = 0;
	data->keys.up = 0;
	data->keys.down = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.minus = 0;
	data->keys.plus = 0;
	data->keys.left_bracket = 0;
	data->keys.right_bracket = 0;
}

void	rt_configure_events(t_data *data)
{
	rt_initialize_keys(data);
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, rt_handle_kpress, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask,
		rt_handle_krelease, data);
	mlx_hook(data->mlx.win, DestroyNotify, StructureNotifyMask,
		rt_handle_close, data);
}
