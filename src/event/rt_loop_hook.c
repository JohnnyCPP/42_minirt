/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loop_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_loop_hook(t_data *data)
{
	int	updated;

	updated = 0;
	updated += rt_move_camera_forw_backw(data);
	updated += rt_move_camera_left_right(data);
	updated += rt_move_camera_up_down(data);
	updated += rt_rotate_camera_event(data);
	updated += rt_resize_diameter(data);
	updated += rt_resize_height(data);
	if (updated > 0)
		rt_render(data);
	return (0);
}
