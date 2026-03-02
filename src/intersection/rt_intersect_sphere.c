/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	void	rt_set_hit(t_hit *hit, double t, t_ray ray, t_sphere *sphere)
{
	t_coordinates	center_to_hit;

	hit->occurred = 1;
	hit->distance = t;
	hit->point = rt_get_point(ray, t);
	center_to_hit = rt_subtract_vector(hit->point, sphere->center);
	hit->normalized = rt_normalize_vector(center_to_hit);
	hit->color = sphere->color;
}

static	double	rt_get_closest_positive(double t1, double t2)
{
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	else if (t1 > EPSILON)
		return (t1);
	else if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

int	rt_intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	t_quadratic		quad;
	t_coordinates	oc;
	double			discriminant;
	double			sqrt_disc;

	oc = rt_subtract_vector(ray.origin, sphere->center);
	quad.a = rt_dotprod_of(ray.direction, ray.direction);
	quad.b = 2.0 * rt_dotprod_of(oc, ray.direction);
	quad.c = rt_get_sqmag(oc) - sphere->radius * sphere->radius;
	discriminant = quad.b * quad.b - 4 * quad.a * quad.c;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	quad.t1 = (-quad.b - sqrt_disc) / (2 * quad.a);
	quad.t2 = (-quad.b + sqrt_disc) / (2 * quad.a);
	quad.t = rt_get_closest_positive(quad.t1, quad.t2);
	if (quad.t < 0)
		return (0);
	rt_set_hit(hit, quad.t, ray, sphere);
	return (1);
}
