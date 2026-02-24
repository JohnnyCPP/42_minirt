/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:20:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/02/24 13:40:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	rt_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static int	rt_is_in_shadow(t_scene *scene, t_hit hit)
{
	t_ray			shadow_ray;
	t_hit			shadow_hit;
	t_coordinates	to_light;
	double			light_dist;

	to_light = rt_subtract_vector(scene->light.source, hit.point);
	light_dist = rt_get_mag(to_light);
	shadow_ray.origin = rt_add_vector(hit.point,
			rt_multiply_vector(hit.normalized, EPSILON_SHADOW));
	shadow_ray.direction = rt_normalize_vector(to_light);
	if (rt_find_closest_object(shadow_ray, scene, &shadow_hit))
	{
		if (shadow_hit.distance < light_dist)
			return (1);
	}
	return (0);
}

static t_color	rt_compute_diffuse(t_scene *scene, t_hit hit)
{
	t_color			result;
	t_coordinates	light_dir;
	double			dot;
	double			intensity;

	light_dir = rt_subtract_vector(scene->light.source, hit.point);
	light_dir = rt_normalize_vector(light_dir);
	dot = rt_dotprod_of(hit.normalized, light_dir);
	if (dot < 0.0)
		dot = 0.0;
	intensity = dot * scene->light.brightness;
	result.red = (int)(hit.color.red * intensity);
	result.green = (int)(hit.color.green * intensity);
	result.blue = (int)(hit.color.blue * intensity);
	return (result);
}

t_color	rt_compute_lighting(t_scene *scene, t_hit hit)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	result;

	ambient.red = (int)(hit.color.red * scene->ambient.ratio);
	ambient.green = (int)(hit.color.green * scene->ambient.ratio);
	ambient.blue = (int)(hit.color.blue * scene->ambient.ratio);
	diffuse = rt_compute_diffuse(scene, hit);
	if (diffuse.red == 0 && diffuse.green == 0 && diffuse.blue == 0)
		return (ambient);
	if (rt_is_in_shadow(scene, hit))
		return (ambient);
	result.red = rt_clamp(ambient.red + diffuse.red, 0, 255);
	result.green = rt_clamp(ambient.green + diffuse.green, 0, 255);
	result.blue = rt_clamp(ambient.blue + diffuse.blue, 0, 255);
	return (result);
}
