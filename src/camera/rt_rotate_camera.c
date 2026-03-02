/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotate_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/02/24 12:30:00 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Rotates a vector around an arbitrary axis using Rodrigues' formula.
 *
 * Rodrigues' rotation formula:
 *     v_rot = v * cos(θ) + (axis × v) * sin(θ) + axis * (axis·v) * (1 - cos(θ))
 *
 * @param v Vector to rotate
 * @param axis Unit vector representing rotation axis
 * @param ang Rotation angle in radians
 * @return t_coordinates Rotated vector
 */
t_coordinates	rt_rotate_axis(t_coordinates v, t_coordinates axis, double ang)
{
	t_coordinates	result;
	t_coordinates	cross;
	double			cos_angle;
	double			sin_angle;
	double			dot;

	cos_angle = cos(ang);
	sin_angle = sin(ang);
	dot = rt_dotprod_of(axis, v);
	cross.x = axis.y * v.z - axis.z * v.y;
	cross.y = axis.z * v.x - axis.x * v.z;
	cross.z = axis.x * v.y - axis.y * v.x;
	result.x = v.x * cos_angle + cross.x * sin_angle
		+ axis.x * dot * (1 - cos_angle);
	result.y = v.y * cos_angle + cross.y * sin_angle
		+ axis.y * dot * (1 - cos_angle);
	result.z = v.z * cos_angle + cross.z * sin_angle
		+ axis.z * dot * (1 - cos_angle);
	return (result);
}

void	rt_pitch_camera(t_camera *camera, double angle)
{
	t_coordinates	right;
	t_coordinates	new_orientation;

	right = rt_get_camera_right(camera);
	new_orientation = rt_rotate_axis(camera->orientation, right, angle);
	camera->orientation = rt_normalize_vector(new_orientation);
}

void	rt_yaw_camera(t_camera *camera, double angle)
{
	t_coordinates	world_up;
	t_coordinates	new_orientation;

	world_up.x = 0.0;
	world_up.y = 1.0;
	world_up.z = 0.0;
	new_orientation = rt_rotate_axis(camera->orientation, world_up, angle);
	camera->orientation = rt_normalize_vector(new_orientation);
}
