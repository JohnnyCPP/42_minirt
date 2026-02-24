/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect_caps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Configures the bottom cap plane of a cylinder.
 *
 * Bottom cap is located at center - (orientation * half_height)
 * and faces downward (negated orientation).
 *
 * @param cyl Cylinder containing cap parameters
 * @param cap Output: plane structure configured as bottom cap
 */
void	rt_set_bottom_cap(t_cylinder *cyl, t_plane *cap)
{
	cap->point = rt_subtract_vector(cyl->center,
			rt_multiply_vector(cyl->orientation, cyl->half_height));
	cap->orientation = rt_negate_vector(cyl->orientation);
	cap->color = cyl->color;
}

/**
 * @brief Configures the top cap plane of a cylinder.
 *
 * Top cap is located at center + (orientation * half_height)
 * and faces upward (orientation).
 *
 * @param cyl Cylinder containing cap parameters
 * @param cap Output: plane structure configured as top cap
 */
void	rt_set_top_cap(t_cylinder *cyl, t_plane *cap)
{
	cap->point = rt_add_vector(cyl->center,
			rt_multiply_vector(cyl->orientation, cyl->half_height));
	cap->orientation = cyl->orientation;
	cap->color = cyl->color;
}

/**
 * @brief Checks if a hit point on a cap plane is within the cap's radius.
 *
 * @param hit_p Point where ray hit the cap plane
 * @param cap_c Center point of the cap
 * @param radius Cylinder radius
 * @return int 1 if point is within radius, 0 otherwise
 */
int	rt_is_in_cap_radius(t_coordinates hit_p, t_coordinates cap_c, double radius)
{
	t_coordinates	to_center;
	double			sq_dist;

	to_center = rt_subtract_vector(hit_p, cap_c);
	sq_dist = rt_get_sqmag(to_center);
	return (sq_dist <= radius * radius + EPSILON);
}

/**
 * @brief Checks if a cap hit is valid and updates the main hit if closer.
 *
 * @param cap_hit Hit info from plane intersection
 * @param cap Plane structure of the cap
 * @param cyl Cylinder being tested
 * @param hit Output: main hit structure to update
 * @return int 1 if valid hit occurred and was closer, 0 otherwise
 */
int	rt_check_cap_hit(t_hit cap_hit, t_plane cap, t_cylinder *cyl, t_hit *hit)
{
	double	y_pos;

	y_pos = rt_dotprod_of(
			rt_subtract_vector(cap_hit.point, cyl->center),
			cyl->orientation);
	if (fabs(y_pos + cyl->half_height) < EPSILON
		|| fabs(y_pos - cyl->half_height) < EPSILON)
	{
		if (rt_is_in_cap_radius(cap_hit.point, cap.point, cyl->radius))
		{
			if (cap_hit.distance < hit->distance)
			{
				*hit = cap_hit;
				hit->normalized = cap.orientation;
				return (1);
			}
		}
	}
	return (0);
}

/**
 * @brief Tests intersection with cylinder caps (top and bottom).
 */
int	rt_intersect_caps(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	t_plane			bottom_cap;
	t_plane			top_cap;
	t_hit			cap_hit;
	int				hit_occurred;

	hit_occurred = 0;
	hit->distance = INFINITY;
	rt_set_bottom_cap(cyl, &bottom_cap);
	rt_set_top_cap(cyl, &top_cap);
	if (rt_intersect_plane(ray, &bottom_cap, &cap_hit))
	{
		if (rt_check_cap_hit(cap_hit, bottom_cap, cyl, hit))
			hit_occurred = 1;
	}
	if (rt_intersect_plane(ray, &top_cap, &cap_hit))
	{
		if (rt_check_cap_hit(cap_hit, top_cap, cyl, hit))
			hit_occurred = 1;
	}
	return (hit_occurred);
}
