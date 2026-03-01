/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:00:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/27 00:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putendl_fd(message, 2);
	return (0);
}

static	void	rt_free_scene_cylinders(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->cylinders)
	{
		while (scene->cylinders[i])
			free(scene->cylinders[i++]);
		free(scene->cylinders);
	}
}

static	void	rt_free_scene_planes(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->planes)
	{
		while (scene->planes[i])
			free(scene->planes[i++]);
		free(scene->planes);
	}
}

static	void	rt_free_scene_spheres(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->spheres)
	{
		while (scene->spheres[i])
			free(scene->spheres[i++]);
		free(scene->spheres);
	}
}

void	rt_free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	rt_free_scene_spheres(scene);
	rt_free_scene_planes(scene);
	rt_free_scene_cylinders(scene);
	ft_bzero(scene, sizeof(t_scene));
}
