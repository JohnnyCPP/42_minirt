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

static	void	rt_set_hit(t_hit *hit, double t, t_ray ray, t_plane *plane)
{
	hit->occurred = 1;
	hit->distance = t;
	hit->point = rt_get_point(ray, t);
	hit->normalized = rt_normalize_vector(plane->orientation);
	hit->color = plane->color;
}

int	rt_intersect_plane(t_ray ray, t_plane *plane, t_hit *hit)
{
	t_coordinates	oc;
	double			denom;
	double			t;

	oc = rt_subtract_vector(ray.origin, plane->point);
	denom = rt_dotprod_of(ray.direction, plane->orientation);
	if (fabs(denom) < EPSILON)
		return (0);
	t = -rt_dotprod_of(oc, plane->orientation) / denom;
	if (t < EPSILON)
		return (0);
	rt_set_hit(hit, t, ray, plane);
	return (1);
}
