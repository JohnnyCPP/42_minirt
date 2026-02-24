/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Creates a hit structure for a cylinder side intersection.
 *
 * @param ray Original ray in world coordinates
 * @param cylinder Cylinder being hit
 * @param t Distance along the ray where hit occurs
 * @return t_hit Complete hit information for the side intersection
 */
static	t_hit	rt_create_side_hit(t_ray ray, t_cylinder *cylinder, double t)
{
	t_hit	hit;

	hit.occurred = 1;
	hit.distance = t;
	hit.point = rt_get_point(ray, t);
	hit.normalized = rt_get_side_normal(hit.point, cylinder);
	hit.color = cylinder->color;
	return (hit);
}

/**
 * @brief Processes a single potential side intersection.
 *
 * Checks if the hit at distance t is within height bounds and
 * updates the main hit if it's closer than the current closest.
 *
 * @param ray Original ray
 * @param cylinder Cylinder being tested
 * @param local Ray in cylinder local coordinates
 * @param t Distance to test
 * @param hit Output: main hit structure to update
 * @return int 1 if hit was processed and updated, 0 otherwise
 */
static	int	rt_process_side_hit(t_side_hit_aux aux)
{
	double		y;
	t_hit		side_hit;

	if (aux.t < EPSILON)
		return (0);
	y = aux.local.origin.y + aux.t * aux.local.direction.y;
	if (!rt_within_height(y, aux.cylinder))
		return (0);
	side_hit = rt_create_side_hit(aux.ray, aux.cylinder, aux.t);
	if (aux.t < aux.hit->distance)
	{
		*aux.hit = side_hit;
		return (1);
	}
	return (0);
}

/**
 * @brief Checks both possible side intersections (t1 and t2).
 *
 * Solves the quadratic for cylinder side intersection and processes
 * both t values if they exist and are valid.
 *
 * @param ray Original ray
 * @param cylinder Cylinder being tested
 * @param local Ray in cylinder local coordinates
 * @param hit Output: main hit structure to update
 * @return int 1 if any side hit was found and closer than current, 0 otherwise
 */
static	int	rt_check_side_intersections(t_ray ray, t_cylinder *cylinder,
		t_ray local, t_hit *hit)
{
	t_side_hit_aux	aux;
	int				hit_occurred;

	hit_occurred = 0;
	aux.ray = ray;
	aux.cylinder = cylinder;
	aux.local = local;
	aux.hit = hit;
	aux.t1 = 0;
	aux.t2 = 0;
	if (!rt_solve_side_quadratic(local, cylinder->radius, &aux.t1, &aux.t2))
		return (0);
	aux.t = aux.t1;
	if (rt_process_side_hit(aux))
		hit_occurred = 1;
	if (fabs(aux.t2 - aux.t1) > EPSILON)
	{
		aux.t = aux.t2;
		if (rt_process_side_hit(aux))
			hit_occurred = 1;
	}
	return (hit_occurred);
}

int	rt_intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_ray	local;
	t_hit	cap_hit;
	int		hit_occurred;

	hit_occurred = 0;
	hit->distance = INFINITY;
	rt_transform_ray(ray, cylinder, &local);
	if (rt_check_side_intersections(ray, cylinder, local, hit))
		hit_occurred = 1;
	if (rt_intersect_caps(ray, cylinder, &cap_hit))
	{
		if (cap_hit.distance < hit->distance)
		{
			hit_occurred = 1;
			*hit = cap_hit;
		}
	}
	return (hit_occurred);
}
