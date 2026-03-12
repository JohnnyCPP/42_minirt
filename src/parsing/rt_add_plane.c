/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_plane.c                                     :+:      :+:    :+:   */
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

int	rt_new_pl(t_plane **aux, t_plane ***planes, t_plane plane)
{
	*aux = (t_plane *) malloc(sizeof(t_plane));
	if (!*aux)
	{
		free(*planes);
		rt_error("Failed to allocate plane");
		return (EXIT_FAILURE);
	}
	**aux = plane;
	return (EXIT_SUCCESS);
}

void	rt_copy_planes(t_scene *scene, t_plane **planes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		planes[i] = scene->planes[i];
		i ++;
	}
}

int	rt_add_plane(t_scene *scene, t_plane plane)
{
	t_plane	**planes;
	t_plane	*aux;
	int		count;

	count = rt_count_objects((void **)scene->planes);
	planes = (t_plane **) malloc(sizeof(t_plane *) * (count + 2));
	if (!planes)
		return (rt_error("Failed to allocate plane array"));
	if (rt_new_pl(&aux, &planes, plane) == EXIT_FAILURE)
		return (0);
	rt_copy_planes(scene, planes, count);
	planes[count] = aux;
	planes[count + 1] = NULL;
	free(scene->planes);
	scene->planes = planes;
	return (1);
}
