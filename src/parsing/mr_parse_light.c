/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mr_parse_light_color(char **tokens, t_light *light)
{
	if (tokens[3])
	{
		if (!mr_parse_color(tokens[3], &light->color))
			return (mr_error("Invalid light color"));
	}
	else
	{
		light->color.r = 255;
		light->color.g = 255;
		light->color.b = 255;
	}
	return (1);
}

int	mr_parse_light(char **tokens, t_light *light)
{
	if (!tokens || !tokens[1] || !tokens[2])
		return (mr_error("Invalid light format"));
	if (light->is_set)
		return (mr_error("Duplicate light"));
	if (!mr_parse_vec3(tokens[1], &light->position))
		return (mr_error("Invalid light position"));
	if (!mr_parse_float(tokens[2], &light->brightness))
		return (mr_error("Invalid light brightness"));
	if (!mr_validate_range(light->brightness, 0.0, 1.0))
		return (mr_error("Light brightness out of range [0.0,1.0]"));
	if (!mr_parse_light_color(tokens, light))
		return (0);
	light->is_set = 1;
	return (1);
}
