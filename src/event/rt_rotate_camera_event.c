/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotate_camera_event.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_rotate_camera_event(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{
		rt_pitch_camera(&data->scene.camera, -CAM_ROT_SPEED);
		return (1);
	}
	else if (keycode == KEY_DOWN)
	{
		rt_pitch_camera(&data->scene.camera, CAM_ROT_SPEED);
		return (1);
	}
	else if (keycode == KEY_LEFT)
	{
		rt_yaw_camera(&data->scene.camera, -CAM_ROT_SPEED);
		return (1);
	}
	else if (keycode == KEY_RIGHT)
	{
		rt_yaw_camera(&data->scene.camera, CAM_ROT_SPEED);
		return (1);
	}
	return (0);
}
