/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_camera_axes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/02/24 12:30:00 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Calculates the right vector (camera's X axis) from orientation.
 *
 * Uses world up vector (0,1,0) cross product with camera orientation
 * to get a vector perpendicular to both.
 */
static	t_coordinates	rt_calculate_right(t_coordinates orientation)
{
	t_coordinates	world_up;
	t_coordinates	right;

	world_up.x = 0.0;
	world_up.y = 1.0;
	world_up.z = 0.0;
	if (fabs(orientation.y) > 0.999)
	{
		world_up.x = 0.0;
		world_up.y = 0.0;
		world_up.z = 1.0;
	}
	right.x = world_up.y * orientation.z - world_up.z * orientation.y;
	right.y = world_up.z * orientation.x - world_up.x * orientation.z;
	right.z = world_up.x * orientation.y - world_up.y * orientation.x;
	return (rt_normalize_vector(right));
}

/**
 * @brief Calculates the up vector (camera's Y axis) from orientation and right.
 *
 * Camera orientation (forward) cross product with right gives the up vector.
 * This ensures a consistent orthonormal basis.
 */
t_coordinates	rt_calculate_up(t_coordinates orientation, t_coordinates right)
{
	t_coordinates	up;

	up.x = orientation.y * right.z - orientation.z * right.y;
	up.y = orientation.z * right.x - orientation.x * right.z;
	up.z = orientation.x * right.y - orientation.y * right.x;
	return (rt_normalize_vector(up));
}

t_coordinates	rt_get_camera_right(t_camera *camera)
{
	return (rt_calculate_right(camera->orientation));
}

t_coordinates	rt_get_camera_up(t_camera *camera)
{
	t_coordinates	right;

	right = rt_get_camera_right(camera);
	return (rt_calculate_up(camera->orientation, right));
}
