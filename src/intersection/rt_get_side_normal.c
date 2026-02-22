/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_side_normal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Computes normal at a point on cylinder side.
 */
t_coordinates	rt_get_side_normal(t_coordinates point, t_cylinder *cyl)
{
	t_coordinates	axis;
	t_coordinates	to_point;
	t_coordinates	normal;

	axis = rt_normalize_vector(cyl->orientation);
	to_point = rt_subtract_vector(point, cyl->center);
	normal = rt_subtract_vector(to_point,
			rt_multiply_vector(axis,
				rt_dotprod_of(to_point, axis)));
	return (rt_normalize_vector(normal));
}
