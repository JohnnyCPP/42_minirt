/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_transform_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Creates orthonormal basis when cylinder axis is aligned with Y.
 * 
 * When axis is nearly (0,1,0), we can use world X as right vector
 * and compute up as cross(axis, right).
 * 
 * @param a Cylinder axis (normalized)
 * @param rgt Output: right vector (camera's X axis)
 * @param up Output: up vector (camera's Y axis)
 */
void	rt_basis_aligned(t_coordinates a, t_coordinates *rgt, t_coordinates *up)
{
	rgt->x = 1.0;
	rgt->y = 0.0;
	rgt->z = 0.0;
	up->x = a.y * rgt->z - a.z * rgt->y;
	up->y = a.z * rgt->x - a.x * rgt->z;
	up->z = a.x * rgt->y - a.y * rgt->x;
}

/**
 * @brief Creates orthonormal basis for general cylinder axis.
 *
 * @param a Cylinder axis (normalized)
 * @param rgt Output: right vector
 * @param up Output: up vector
 */
void	rt_basis_general(t_coordinates a, t_coordinates *rgt, t_coordinates *up)
{
	rgt->x = 1.0 * a.z - a.y * 0.0;
	rgt->y = a.z * 0.0 - a.x * 0.0;
	rgt->z = a.x * 1.0 - 0.0 * a.y;
	*rgt = rt_normalize_vector(*rgt);
	up->x = a.y * rgt->z - a.z * rgt->y;
	up->y = a.z * rgt->x - a.x * rgt->z;
	up->z = a.x * rgt->y - a.y * rgt->x;
	*up = rt_normalize_vector(*up);
}

/**
 * @brief Transforms ray into cylinder's local coordinate system.
 *
 * We create a basis where the cylinder axis is the Y axis.
 * This simplifies the intersection math significantly.
 */
void	rt_transform_ray(t_ray ray, t_cylinder *cyl, t_ray *local_ray)
{
	t_coordinates	axis;
	t_coordinates	right;
	t_coordinates	up;
	t_coordinates	to_local;

	axis = rt_normalize_vector(cyl->orientation);
	if (fabs(axis.y) > 0.999)
		rt_basis_aligned(axis, &right, &up);
	else
		rt_basis_general(axis, &right, &up);
	to_local = rt_subtract_vector(ray.origin, cyl->center);
	local_ray->origin.x = rt_dotprod_of(to_local, right);
	local_ray->origin.y = rt_dotprod_of(to_local, axis);
	local_ray->origin.z = rt_dotprod_of(to_local, up);
	local_ray->direction.x = rt_dotprod_of(ray.direction, right);
	local_ray->direction.y = rt_dotprod_of(ray.direction, axis);
	local_ray->direction.z = rt_dotprod_of(ray.direction, up);
	local_ray->direction = rt_normalize_vector(local_ray->direction);
}
