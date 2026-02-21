/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
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

	up.x = right.y * orientation.z - right.z * orientation.y;
	up.y = right.z * orientation.x - right.x * orientation.z;
	up.z = right.x * orientation.y - right.y * orientation.x;
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

t_coordinates	rt_get_viewport_point(t_camera *camera, double x, double y)
{
	t_coordinates	right;
	t_coordinates	up;
	t_coordinates	forward;
	t_coordinates	result;
	double			fov_scale;

	right = rt_get_camera_right(camera);
	up = rt_get_camera_up(camera);
	forward = rt_normalize_vector(camera->orientation);
	fov_scale = tan((camera->fov * M_PI / 180.0) / 2.0);
	result = camera->viewpoint;
	result = rt_add_vector(result,
			rt_multiply_vector(right,
				x * fov_scale * ((double) WIN_WIDTH / WIN_HEIGHT)));
	result = rt_add_vector(result, rt_multiply_vector(up, y * fov_scale));
	result = rt_add_vector(result, forward);
	return (result);
}

t_ray	rt_get_camera_ray(t_camera *camera, int x, int y)
{
	t_coordinates	viewport_point;
	t_coordinates	ray_direction;
	double			x_ratio;
	double			y_ratio;

	x_ratio = (2.0 * (x + 0.5) / WIN_WIDTH) - 1.0;
	y_ratio = 1.0 - (2.0 * (y + 0.5) / WIN_HEIGHT);
	viewport_point = rt_get_viewport_point(camera, x_ratio, y_ratio);
	ray_direction = rt_subtract_vector(viewport_point, camera->viewpoint);
	return (rt_create_ray(camera->viewpoint, ray_direction));
}
