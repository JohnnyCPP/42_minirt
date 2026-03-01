/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_cylinder.c                                  :+:      :+:    :+:   */
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

int	rt_new_cyl(t_cylinder **aux, t_cylinder ***cylinders, t_cylinder cylinder)
{
	*aux = (t_cylinder *) malloc(sizeof(t_cylinder));
	if (!aux)
	{
		free(*cylinders);
		*cylinders = NULL;
		rt_error("Failed to allocate cylinder");
		return (EXIT_FAILURE);
	}
	**aux = cylinder;
	return (EXIT_SUCCESS);
}

void	rt_copy_cylinders(t_scene *scene, t_cylinder **cylinders, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		cylinders[i] = scene->cylinders[i];
		i ++;
	}
}

int	rt_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	t_cylinder	**cylinders;
	t_cylinder	*aux;
	int			count;

	count = rt_count_objects((void **)scene->cylinders);
	cylinders = (t_cylinder **) malloc(sizeof(t_cylinder *) * (count + 2));
	if (!cylinders)
		return (rt_error("Failed to allocate cylinder array"));
	if (rt_new_cyl(&aux, &cylinders, cylinder) == EXIT_FAILURE)
		return (0);
	rt_copy_cylinders(scene, cylinders, count);
	cylinders[count] = aux;
	cylinders[count + 1] = NULL;
	free(scene->cylinders);
	scene->cylinders = cylinders;
	return (1);
}
