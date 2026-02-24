/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	count_objects(void **objects)
{
	int	count;

	count = 0;
	if (!objects)
		return (0);
	while (objects[count])
		count++;
	return (count);
}

int	rt_add_sphere(t_scene *scene, t_sphere sphere)
{
	t_sphere	**new;
	t_sphere	*sphere_ptr;
	int			count;
	int			i;

	count = count_objects((void **)scene->spheres);
	new = malloc(sizeof(t_sphere *) * (count + 2));
	if (!new)
		return (rt_error("Failed to allocate sphere array"));
	sphere_ptr = malloc(sizeof(t_sphere));
	if (!sphere_ptr)
	{
		free(new);
		return (rt_error("Failed to allocate sphere"));
	}
	*sphere_ptr = sphere;
	i = 0;
	while (i < count)
	{
		new[i] = scene->spheres[i];
		i++;
	}
	new[i] = sphere_ptr;
	new[i + 1] = NULL;
	free(scene->spheres);
	scene->spheres = new;
	return (1);
}

int	rt_add_plane(t_scene *scene, t_plane plane)
{
	t_plane	**new;
	t_plane	*plane_ptr;
	int		count;
	int		i;

	count = count_objects((void **)scene->planes);
	new = malloc(sizeof(t_plane *) * (count + 2));
	if (!new)
		return (rt_error("Failed to allocate plane array"));
	plane_ptr = malloc(sizeof(t_plane));
	if (!plane_ptr)
	{
		free(new);
		return (rt_error("Failed to allocate plane"));
	}
	*plane_ptr = plane;
	i = 0;
	while (i < count)
	{
		new[i] = scene->planes[i];
		i++;
	}
	new[i] = plane_ptr;
	new[i + 1] = NULL;
	free(scene->planes);
	scene->planes = new;
	return (1);
}

int	rt_add_cylinder(t_scene *scene, t_cylinder cyl)
{
	t_cylinder	**new;
	t_cylinder	*cyl_ptr;
	int			count;
	int			i;

	count = count_objects((void **)scene->cylinders);
	new = malloc(sizeof(t_cylinder *) * (count + 2));
	if (!new)
		return (rt_error("Failed to allocate cylinder array"));
	cyl_ptr = malloc(sizeof(t_cylinder));
	if (!cyl_ptr)
	{
		free(new);
		return (rt_error("Failed to allocate cylinder"));
	}
	*cyl_ptr = cyl;
	i = 0;
	while (i < count)
	{
		new[i] = scene->cylinders[i];
		i++;
	}
	new[i] = cyl_ptr;
	new[i + 1] = NULL;
	free(scene->cylinders);
	scene->cylinders = new;
	return (1);
}
