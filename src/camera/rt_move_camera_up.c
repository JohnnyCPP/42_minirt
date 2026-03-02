/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_move_camera_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/02/24 12:30:00 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	rt_move_camera_up(t_camera *camera, double speed)
{
	t_coordinates	up;
	t_coordinates	movement;

	up = rt_get_camera_up(camera);
	movement = rt_multiply_vector(up, speed);
	camera->viewpoint = rt_add_vector(camera->viewpoint, movement);
}
