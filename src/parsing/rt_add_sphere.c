/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	rt_count_objects(void **objects)
{
	int	count;

	count = 0;
	if (!objects)
		return (0);
	while (objects[count])
		count++;
	return (count);
}

int	rt_new_sp(t_sphere **aux, t_sphere ***spheres, t_sphere sphere)
{
	*aux = (t_sphere *) malloc(sizeof(t_sphere));
	if (!aux)
	{
		free(*spheres);
		*spheres = NULL;
		rt_error("Failed to allocate sphere");
		return (EXIT_FAILURE);
	}
	**aux = sphere;
	return (EXIT_SUCCESS);
}

void	rt_copy_spheres(t_scene *scene, t_sphere **spheres, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		spheres[i] = scene->spheres[i];
		i ++;
	}
}

int	rt_add_sphere(t_scene *scene, t_sphere sphere)
{
	t_sphere	**spheres;
	t_sphere	*aux;
	int			count;

	count = rt_count_objects((void **)scene->spheres);
	spheres = (t_sphere **) malloc(sizeof(t_sphere *) * (count + 2));
	if (!spheres)
		return (rt_error("Failed to allocate sphere array"));
	if (rt_new_sp(&aux, &spheres, sphere) == EXIT_FAILURE)
		return (0);
	rt_copy_spheres(scene, spheres, count);
	spheres[count] = aux;
	spheres[count + 1] = NULL;
	free(scene->spheres);
	scene->spheres = spheres;
	return (1);
}
