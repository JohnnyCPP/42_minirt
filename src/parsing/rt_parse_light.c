/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Parses light color with default fallback.
 *
 * Light color is optional in the .rt format. If not provided,
 * defaults to white (255,255,255).
 *
 * Format variations:
 *     With color:  L  -40,0,30  0.7  255,255,255
 *     Without:     L  -40,0,30  0.7
 *
 * @param tokens Token array (may have 3 or 4 tokens)
 * @param light Light structure to populate
 * @return int 1 always (color is optional)
 */
static int	rt_parse_light_color(char **tokens, t_light *light)
{
	if (tokens[3])
	{
		if (!rt_parse_color(tokens[3], &light->color))
			return (rt_error("Invalid light color"));
	}
	else
	{
		light->color.red = 255;
		light->color.green = 255;
		light->color.blue = 255;
	}
	return (1);
}

int	rt_parse_light(char **tokens, t_light *light)
{
	if (!tokens || !tokens[1] || !tokens[2])
		return (rt_error("Invalid light format"));
	if (!rt_parse_vec3(tokens[1], &light->source))
		return (rt_error("Invalid light position"));
	if (!rt_parse_float(tokens[2], &light->brightness))
		return (rt_error("Invalid light brightness"));
	if (!rt_validate_range(light->brightness, 0.0, 1.0))
		return (rt_error("Light brightness out of range [0.0,1.0]"));
	if (!rt_parse_light_color(tokens, light))
		return (0);
	return (1);
}
