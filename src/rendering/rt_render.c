/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:05:07 by igenez-y          #+#    #+#             */
/*   Updated: 2026/02/24 12:10:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_get_color_int(t_color color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}


/*
 * @brief Computes the color for a hit point (ambient only for now).
 *
 * Currently implements only ambient lighting as per mandatory part:
 * color = object_color * ambient_ratio
 *
 * @param scene Scene containing ambient lighting info
 * @param hit Hit point information
 * @return t_color Final color after lighting calculations
 */


/* static	t_color	rt_compute_lighting(t_scene *scene, t_hit hit)
{
	t_color	result;

	result.red = (int)(hit.color.red * scene->ambient.ratio);
	result.green = (int)(hit.color.green * scene->ambient.ratio);
	result.blue = (int)(hit.color.blue * scene->ambient.ratio);
	return (result);
}*/

static	void	rt_set_background(t_color *color)
{
	color->red = 0;
	color->green = 0;
	color->blue = 0;
}

void	rt_render(t_data *data)
{
	t_color	pixel_color;
	t_ray	ray;
	t_hit	hit;
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = rt_get_camera_ray(&data->scene.camera, x, y);
			if (rt_find_closest_object(ray, &data->scene, &hit))
				pixel_color = rt_compute_lighting(&data->scene, hit);
			else
				rt_set_background(&pixel_color);
			rt_put_pxl(&data->mlx.img, x, y, rt_get_color_int(pixel_color));
			x ++;
		}
		y ++;
	}
	mlx_put_image_to_window(data->mlx.xvar, data->mlx.win,
		data->mlx.img.img, 0, 0);
}
