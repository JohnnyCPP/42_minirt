/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_mock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * Parsed spheres need to be freed at the end.
 */
void	rt_mock_spheres(t_scene *scene)
{
	t_sphere	**spheres;
	int			amount;

	scene->spheres = NULL;
	amount = 1;
	spheres = (t_sphere **) ft_calloc(amount + 1, sizeof(t_sphere *));
	if (!spheres)
		return ;
	spheres[0] = (t_sphere *) ft_calloc(1, sizeof(t_sphere));
	if (!spheres[0])
	{
		free(spheres);
		return ;
	}
	spheres[0]->center.x = 0.0;
	spheres[0]->center.y = 0.0;
	spheres[0]->center.z = 20.6;
	spheres[0]->diameter = 12.6;
	spheres[0]->color.red = 10;
	spheres[0]->color.green = 0;
	spheres[0]->color.blue = 255;
	spheres[amount] = NULL;
	scene->spheres = spheres;
}

static	void	rt_assign_planes(t_plane **planes, int amount)
{
	planes[0]->point.x = 0.0;
	planes[0]->point.y = 0.0;
	planes[0]->point.z = -10.0;
	planes[0]->orientation.x = 0.0;
	planes[0]->orientation.y = 1.0;
	planes[0]->orientation.z = 0.0;
	planes[0]->color.red = 0;
	planes[0]->color.green = 0;
	planes[0]->color.blue = 255;
	planes[amount] = NULL;
}

/**
 * Parsed planes need to be freed at the end.
 */
void	rt_mock_planes(t_scene *scene)
{
	t_plane		**planes;
	int			amount;

	scene->planes = NULL;
	amount = 1;
	planes = (t_plane **) ft_calloc(amount + 1, sizeof(t_plane *));
	if (!planes)
		return ;
	planes[0] = (t_plane *) ft_calloc(1, sizeof(t_plane));
	if (!planes[0])
	{
		free(planes);
		return ;
	}
	rt_assign_planes(planes, amount);
	scene->planes = planes;
}

static	void	rt_assign_cylinders(t_cylinder **cylinders, int amount)
{
	cylinders[0]->center.x = 0.0;
	cylinders[0]->center.y = 0.0;
	cylinders[0]->center.z = 20.6;
	cylinders[0]->orientation.x = 0.0;
	cylinders[0]->orientation.y = 1.0;
	cylinders[0]->orientation.z = 0.0;
	cylinders[0]->diameter = 12.6;
	cylinders[0]->height = 12.6;
	cylinders[0]->color.red = 10;
	cylinders[0]->color.green = 0;
	cylinders[0]->color.blue = 255;
	cylinders[amount] = NULL;
}

/**
 * Parsed cylinders need to be freed at the end.
 */
void	rt_mock_cylinders(t_scene *scene)
{
	t_cylinder	**cylinders;
	int			amount;

	scene->cylinders = NULL;
	amount = 1;
	cylinders = (t_cylinder **) ft_calloc(amount + 1, sizeof(t_cylinder *));
	if (!cylinders)
		return ;
	cylinders[0] = (t_cylinder *) ft_calloc(1, sizeof(t_cylinder));
	if (!cylinders[0])
	{
		free(cylinders);
		return ;
	}
	rt_assign_cylinders(cylinders, amount);
	scene->cylinders = cylinders;
}
