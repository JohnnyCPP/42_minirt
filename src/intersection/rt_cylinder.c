/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Transforms ray into cylinder's local coordinate system.
 *
 * We create a basis where the cylinder axis is the Y axis.
 * This simplifies the intersection math significantly.
 */
static	void	rt_transform_ray(t_ray ray, t_cylinder *cyl, t_ray *local_ray)
{
	t_coordinates	axis;
	t_coordinates	right;
	t_coordinates	up;
	t_coordinates	to_local;

	axis = rt_normalize_vector(cyl->orientation);
	if (fabs(axis.y) > 0.999)
	{
		right.x = 1.0;
		right.y = 0.0;
		right.z = 0.0;
		up.x = axis.y * right.z - axis.z * right.y;
		up.y = axis.z * right.x - axis.x * right.z;
		up.z = axis.x * right.y - axis.y * right.x;
	}
	else
	{
		right.x = 1.0 * axis.z - axis.y * 0.0;
		right.y = axis.z * 0.0 - axis.x * 0.0;
		right.z = axis.x * 1.0 - 0.0 * axis.y;
		right = rt_normalize_vector(right);
		up.x = axis.y * right.z - axis.z * right.y;
		up.y = axis.z * right.x - axis.x * right.z;
		up.z = axis.x * right.y - axis.y * right.x;
		up = rt_normalize_vector(up);
	}
	to_local = rt_subtract_vector(ray.origin, cyl->center);
	local_ray->origin.x = rt_dotprod_of(to_local, right);
	local_ray->origin.y = rt_dotprod_of(to_local, axis);
	local_ray->origin.z = rt_dotprod_of(to_local, up);
	local_ray->direction.x = rt_dotprod_of(ray.direction, right);
	local_ray->direction.y = rt_dotprod_of(ray.direction, axis);
	local_ray->direction.z = rt_dotprod_of(ray.direction, up);
	local_ray->direction = rt_normalize_vector(local_ray->direction);
}

/**
 * @brief Solves quadratic for cylinder side intersection.
 *
 * In local coordinates, cylinder is x² + z² = r², infinite in y.
 */
int	rt_solve_side_quadratic(t_ray local, double r, double *t1, double *t2)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = local.direction.x * local.direction.x
		+ local.direction.z * local.direction.z;
	if (a < EPSILON)
		return (0);
	b = 2.0 * (local.origin.x * local.direction.x
			+ local.origin.z * local.direction.z);
	c = local.origin.x * local.origin.x
		+ local.origin.z * local.origin.z - r * r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (0);
	*t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	*t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (1);
}

/**
 * @brief Checks if a point on infinite cylinder is within height bounds.
 */
static	int	rt_within_height(double y, t_cylinder *cyl)
{
	return (fabs(y) <= cyl->half_height + EPSILON);
}

/**
 * @brief Computes normal at a point on cylinder side.
 */
static	t_coordinates	rt_get_side_normal(t_coordinates point, t_cylinder *cyl)
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

/**
 * @brief Tests intersection with cylinder caps (top and bottom).
 */
static	int	rt_intersect_caps(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	t_coordinates	to_center;
	t_plane			cap;
	t_hit			cap_hit;
	int				hit_occurred;
	double			y_pos;

	hit_occurred = 0;
	hit->distance = INFINITY;
	cap.point = rt_subtract_vector(cyl->center,
			rt_multiply_vector(cyl->orientation, cyl->half_height));
	cap.orientation = rt_negate_vector(cyl->orientation);
	cap.color = cyl->color;
	if (rt_intersect_plane(ray, &cap, &cap_hit))
	{
		y_pos = rt_dotprod_of(
				rt_subtract_vector(cap_hit.point, cyl->center),
				cyl->orientation);
		if (fabs(y_pos + cyl->half_height) < EPSILON)
		{
			to_center = rt_subtract_vector(cap_hit.point, cap.point);
			if (rt_get_sqmag(to_center) <= cyl->radius * cyl->radius + EPSILON)
			{
				if (cap_hit.distance < hit->distance)
				{
					hit_occurred = 1;
					*hit = cap_hit;
					hit->normalized = cap.orientation;
				}
			}
		}
	}
	cap.point = rt_add_vector(cyl->center,
			rt_multiply_vector(cyl->orientation, cyl->half_height));
	cap.orientation = cyl->orientation;
	if (rt_intersect_plane(ray, &cap, &cap_hit))
	{
		y_pos = rt_dotprod_of(
				rt_subtract_vector(cap_hit.point, cyl->center),
				cyl->orientation);
		if (fabs(y_pos - cyl->half_height) < EPSILON)
		{
			to_center = rt_subtract_vector(cap_hit.point, cap.point);
			if (rt_get_sqmag(to_center) <= cyl->radius * cyl->radius + EPSILON)
			{
				if (cap_hit.distance < hit->distance)
				{
					hit_occurred = 1;
					*hit = cap_hit;
					hit->normalized = cap.orientation;
				}
			}
		}
	}
	return (hit_occurred);
}

int	rt_intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_ray	local;
	t_hit	side_hit;
	t_hit	cap_hit;
	double	t1;
	double	t2;
	double	y1;
	double	y2;
	int		hit_occurred;

	hit_occurred = 0;
	hit->distance = INFINITY;
	rt_transform_ray(ray, cylinder, &local);
	if (rt_solve_side_quadratic(local, cylinder->radius, &t1, &t2))
	{
		if (t1 > EPSILON)
		{
			y1 = local.origin.y + t1 * local.direction.y;
			if (rt_within_height(y1, cylinder))
			{
				side_hit.occurred = 1;
				side_hit.distance = t1;
				side_hit.point = rt_get_point(ray, t1);
				side_hit.normalized = rt_get_side_normal(
						side_hit.point, cylinder);
				side_hit.color = cylinder->color;
				if (t1 < hit->distance)
				{
					hit_occurred = 1;
					*hit = side_hit;
				}
			}
		}
		if (t2 > EPSILON && fabs(t2 - t1) > EPSILON)
		{
			y2 = local.origin.y + t2 * local.direction.y;
			if (rt_within_height(y2, cylinder))
			{
				side_hit.occurred = 1;
				side_hit.distance = t2;
				side_hit.point = rt_get_point(ray, t2);
				side_hit.normalized = rt_get_side_normal(
						side_hit.point, cylinder);
				side_hit.color = cylinder->color;
				if (t2 < hit->distance)
				{
					hit_occurred = 1;
					*hit = side_hit;
				}
			}
		}
	}
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
