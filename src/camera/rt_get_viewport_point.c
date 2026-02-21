/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_viewport_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

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
