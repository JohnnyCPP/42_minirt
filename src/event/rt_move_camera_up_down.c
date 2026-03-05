/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_move_camera_up_down.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_move_camera_up_down(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->keys.space)
	{
		rt_move_camera_up(&data->scene.camera, CAM_MOV_SPEED);
		moved = 1;
	}
	if (data->keys.left_ctrl)
	{
		rt_move_camera_down(&data->scene.camera, CAM_MOV_SPEED);
		moved = 1;
	}
	return (moved);
}
