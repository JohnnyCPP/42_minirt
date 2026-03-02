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

int	rt_move_camera_up_down(int keycode, t_data *data)
{
	if (keycode == KEY_SPACE)
	{
		rt_move_camera_up(&data->scene.camera, CAM_MOV_SPEED);
		return (1);
	}
	else if (keycode == KEY_LEFT_CTRL)
	{
		rt_move_camera_down(&data->scene.camera, CAM_MOV_SPEED);
		return (1);
	}
	return (0);
}
