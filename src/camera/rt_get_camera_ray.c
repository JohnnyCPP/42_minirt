/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_camera_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

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
