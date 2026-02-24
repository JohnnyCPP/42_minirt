/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_sphere(char **tokens, t_sphere *sphere)
{
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (rt_error("Invalid sphere format"));
	if (!rt_parse_vec3(tokens[1], &sphere->center))
		return (rt_error("Invalid sphere center"));
	if (!rt_parse_float(tokens[2], &sphere->diameter))
		return (rt_error("Invalid sphere diameter"));
	if (sphere->diameter <= 0.0)
		return (rt_error("Sphere diameter must be positive"));
	if (!rt_parse_color(tokens[3], &sphere->color))
		return (rt_error("Invalid sphere color"));
	return (1);
}
