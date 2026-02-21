/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_find_closest_cylinder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:05:07 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/18 21:01:32 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_find_closest_cylinder(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_hit	aux;
	int		i;
	int		hit_occurred;

	i = 0;
	hit_occurred = 0;
	hit->distance = INFINITY;
	if (!scene->cylinders)
		return (0);
	while (scene->cylinders[i] != NULL)
	{
		if (rt_intersect_cylinder(ray, scene->cylinders[i], &aux))
		{
			if (aux.distance < hit->distance)
			{
				hit_occurred = 1;
				*hit = aux;
			}
		}
		i ++;
	}
	return (hit_occurred);
}
