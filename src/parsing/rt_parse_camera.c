/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_parse_camera(char **tokens, t_camera *camera)
{
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (rt_error("Invalid camera format"));
	if (!rt_parse_vec3(tokens[1], &camera->viewpoint))
		return (rt_error("Invalid camera position"));
	if (!rt_parse_vec3(tokens[2], &camera->orientation))
		return (rt_error("Invalid camera orientation"));
	if (!rt_check_vec_range(camera->orientation, -1.0, 1.0))
		return (rt_error("Camera orientation out of range [-1,1]"));
	if (!rt_validate_normalized(camera->orientation))
		return (rt_error("Camera orientation is zero vector"));
	camera->orientation = rt_normalize_vector(camera->orientation);
	camera->fov = ft_atoi(tokens[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (rt_error("Camera FOV out of range [0,180]"));
	return (1);
}
