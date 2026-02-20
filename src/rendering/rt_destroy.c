/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	void	rt_destroy_mlx(t_minilib *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->xvar, mlx->img.img);
	if (mlx->win)
		mlx_destroy_window(mlx->xvar, mlx->win);
	if (mlx->xvar)
	{
		mlx_destroy_display(mlx->xvar);
		free(mlx->xvar);
	}
}

static	void	rt_destroy_spheres(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->spheres[i] != NULL)
	{
		free(scene->spheres[i]);
		scene->spheres[i] = NULL;
		i ++;
	}
	if (scene->spheres != NULL)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}
}

static	void	rt_destroy_planes(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->planes[i] != NULL)
	{
		free(scene->planes[i]);
		scene->planes[i] = NULL;
		i ++;
	}
	if (scene->planes != NULL)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
}

static	void	rt_destroy_cylinders(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->cylinders[i] != NULL)
	{
		free(scene->cylinders[i]);
		scene->cylinders[i] = NULL;
		i ++;
	}
	if (scene->cylinders != NULL)
	{
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
}

static	void	rt_destroy_scene(t_scene *scene)
{
	rt_destroy_spheres(scene);
	rt_destroy_planes(scene);
	rt_destroy_cylinders(scene);
}

void	rt_destroy(t_data *data)
{
	rt_destroy_mlx(&data->mlx);
	rt_destroy_scene(&data->scene);
}
