/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_find_closest_object.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:05:07 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/18 21:01:32 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	void	rt_update_hit(int *hit_occurred, t_hit *hit, t_hit aux)
{
	if (!*hit_occurred || aux.distance < hit->distance)
	{
		*hit_occurred = 1;
		*hit = aux;
	}
}

int	rt_find_closest_object(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_hit	aux;
	int		hit_occurred;

	hit_occurred = 0;
	hit->distance = INFINITY;
	if (rt_find_closest_sphere(ray, scene, &aux))
	{
		hit_occurred = 1;
		*hit = aux;
	}
	if (rt_find_closest_plane(ray, scene, &aux))
		rt_update_hit(&hit_occurred, hit, aux);
	if (rt_find_closest_cylinder(ray, scene, &aux))
		rt_update_hit(&hit_occurred, hit, aux);
	return (hit_occurred);
}
