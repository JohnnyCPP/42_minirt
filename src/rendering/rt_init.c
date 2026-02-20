/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	int	rt_init_mlx(t_minilib *mlx)
{
	mlx->xvar = mlx_init();
	if (!mlx->xvar)
		return (EXIT_ERROR);
	mlx->win = mlx_new_window(mlx->xvar, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx->win)
	{
		free(mlx->xvar);
		return (EXIT_ERROR);
	}
	mlx->img.img = mlx_new_image(mlx->xvar, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img)
	{
		mlx_destroy_window(mlx->xvar, mlx->win);
		free(mlx->xvar);
		return (EXIT_ERROR);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel,
			&mlx->img.line_length,
			&mlx->img.endian);
	return (EXIT_SUCCESS);
}

/**
 * Parsed spheres need to be freed at the end.
 */
static	void	rt_mock_spheres(t_scene *scene)
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

/**
 * Parsed planes need to be freed at the end.
 */
static	void	rt_mock_planes(t_scene *scene)
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
	scene->planes = planes;
}

/**
 * Parsed cylinders need to be freed at the end.
 */
static	void	rt_mock_cylinders(t_scene *scene)
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
	scene->cylinders = cylinders;
}

/**
 * Adding magic numbers to mock the parsing of a scene description.
 * 
 * TODO: integrate the parsing of the scene file in this step
 * TODO: define default values for the "single entities" 
 *       to avoid undefined behaviors.
 *       ("single entities" can only be declared once in the scene)
 *         - ambient lighting
 *         - camera
 *         - light
 * TODO: sanitize user input of the scene file to avoid undefined behaviors
 *         - ambient lighting
 *           - ratio, color
 *         - camera
 *           - viewpoint, orientation, fov
 *         - light
 *           - source, brightness, color
 *         - spheres
 *           - center, diameter, color
 *         - planes
 *           - point, orientation, color
 *         - cylinders
 *           - center, orientation, diameter, height, color
 * TODO: define a behavior in case "single entities" are missing in the scene
 *         - ambient lighting
 *         - camera
 *         - light
 */
static	int	rt_init_scene(t_scene *scene)
{
	scene->ambient.ratio = 0.2;
	scene->ambient.color.red = 255;
	scene->ambient.color.green = 255;
	scene->ambient.color.blue = 255;
	scene->camera.viewpoint.x = -50.0;
	scene->camera.viewpoint.y = 0.0;
	scene->camera.viewpoint.z = 20.0;
	scene->camera.orientation.x = 0.0;
	scene->camera.orientation.y = 0.0;
	scene->camera.orientation.z = 1.0;
	scene->camera.fov = 70;
	scene->light.source.x = -40.0;
	scene->light.source.y = 50.0;
	scene->light.source.z = 0.0;
	scene->light.brightness = 0.6;
	scene->light.color.red = 255;
	scene->light.color.green = 255;
	scene->light.color.blue = 255;
	rt_mock_spheres(scene);
	rt_mock_planes(scene);
	rt_mock_cylinders(scene);
	return (EXIT_SUCCESS);
}

int	rt_init(t_data *data)
{
	if (rt_init_mlx(&data->mlx) == EXIT_ERROR)
		return (EXIT_ERROR);
	return (rt_init_scene(&data->scene));
}
