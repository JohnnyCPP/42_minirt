/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_h_kpress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_h_kpress(int keycode, t_data *data)
{
	rt_destroy_on_esc(keycode, data);
	if (rt_move_camera_up_down(keycode, data) == 1)
		rt_render(data);
	if (rt_move_camera_forw_backw(keycode, data) == 1)
		rt_render(data);
	if (rt_move_camera_left_right(keycode, data) == 1)
		rt_render(data);
	if (rt_rotate_camera_event(keycode, data) == 1)
		rt_render(data);
	if (rt_select_object(keycode, data) == 1)
		rt_render(data);
	if (rt_resize_diameter(keycode, data) == 1)
		rt_render(data);
	if (rt_resize_height(keycode, data) == 1)
		rt_render(data);
	return (0);
}
