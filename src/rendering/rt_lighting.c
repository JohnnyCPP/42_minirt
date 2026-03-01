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

/**
 * @brief Clamps an integer value between a minimum and maximum range.
 *
 * Ensures a color component stays within valid RGB range [0, 255].
 * If value is below min, returns min; if above max, returns max;
 * otherwise returns the original value.
 *
 * @param value The integer value to clamp
 * @param min The minimum allowed value (typically 0)
 * @param max The maximum allowed value (typically 255)
 * @return int The clamped value within [min, max]
 */
static int	rt_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/**
 * @brief Determines if a point is in shadow by casting a ray toward the light.
 *
 * Implements hard shadows by testing if any object occludes the light source.
 * The shadow ray is cast from the hit point (slightly offset to avoid
 * self-intersection) toward the light position.
 *
 * Visual representation:
 *
 *                    Light source
 *                         ●
 *                         |
 *                         | shadow_ray
 *                         |
 *                         |
 *                    ┌────┴────┐
 *                    │  Shadow  │
 *                    │  Object  │
 *                    └────┬────┘
 *                         │
 *                         ● Hit point
 *                         |
 *                    [offset]
 *                         ● Shadow ray origin
 *
 * The shadow ray origin is offset along the surface normal by EPSILON_SHADOW
 * to prevent the ray from intersecting the same surface due to floating-point
 * precision errors.
 *
 * @param scene Pointer to scene containing light and objects
 * @param hit The hit point data (position, normal, etc.)
 * @return int 1 if point is in shadow (occluded), 0 otherwise
 *
 * @note Uses EPSILON_SHADOW (1e-4) to offset ray origin along normal.
 *       This value was chosen as a trade-off:
 *       - Large enough to avoid self-intersection
 *       - Small enough to not miss nearby occluders
 *
 * @see EPSILON_SHADOW defined in minirt_constants.h
 */
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

/**
 * @brief Computes the diffuse lighting contribution at a hit point.
 *
 * Implements the diffuse component of the Phong reflection model using
 * Lambert's cosine law. The intensity is proportional to the cosine of the
 * angle between the surface normal and the light direction.
 *
 * Mathematical formulation:
 *     diffuse = k_d * I * max(0, n · l)
 *
 * Where:
 *     - k_d is the surface's diffuse color (object color)
 *     - I is the light brightness (0.0 to 1.0)
 *     - n is the surface normal (unit vector)
 *     - l is the light direction (unit vector from point to light)
 *     - n · l is the dot product (cosine of angle between vectors)
 *
 * Visual representation:
 *
 *                    Light
 *                      ●
 *                      ╲
 *                       ╲ l (light direction)
 *                        ╲
 *                         ╲    ↑ n (normal)
 *                          ╲   │
 *                           ╲  │
 *                            ╲ │
 *                             ╲│
 *                              ● Hit point
 *
 * The dot product n·l gives:
 *     - 1.0 when light hits directly (0° angle)
 *     - 0.0 when light is perpendicular (90° angle)
 *     - Negative when light is behind surface (clamped to 0)
 *
 * @param scene Pointer to scene containing light source
 * @param hit The hit point data (position, normal, color)
 * @return t_color The diffuse contribution (may be black if no diffuse)
 *
 * @note This function only computes diffuse, not ambient or specular.
 *       The result should be added to ambient contribution and may be
 *       reduced by shadows.
 *
 * @warning The returned color values are not clamped - caller must ensure
 *          final sum stays within [0, 255] range.
 */
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
