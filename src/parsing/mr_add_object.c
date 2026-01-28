/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_add_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mr_add_sphere(t_objects *objs, t_sphere sphere)
{
	t_sphere	*new;
	int			i;

	new = malloc(sizeof(t_sphere) * (objs->sphere_count + 1));
	if (!new)
		return (mr_error("Failed to allocate sphere"));
	i = 0;
	while (i < objs->sphere_count)
	{
		new[i] = objs->spheres[i];
		i++;
	}
	new[i] = sphere;
	free(objs->spheres);
	objs->spheres = new;
	objs->sphere_count++;
	return (1);
}

int	mr_add_plane(t_objects *objs, t_plane plane)
{
	t_plane	*new;
	int		i;

	new = malloc(sizeof(t_plane) * (objs->plane_count + 1));
	if (!new)
		return (mr_error("Failed to allocate plane"));
	i = 0;
	while (i < objs->plane_count)
	{
		new[i] = objs->planes[i];
		i++;
	}
	new[i] = plane;
	free(objs->planes);
	objs->planes = new;
	objs->plane_count++;
	return (1);
}

int	mr_add_cylinder(t_objects *objs, t_cylinder cyl)
{
	// to be implemented
}
