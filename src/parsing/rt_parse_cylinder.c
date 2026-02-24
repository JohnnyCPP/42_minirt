/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_validate_cylinder_data(t_cylinder *cyl)
{
	if (!mr_check_vec_range(cyl->axis, -1.0, 1.0))
		return (mr_error("Cylinder axis out of range [-1,1]"));
	if (!mr_validate_normalized(cyl->axis))
		return (mr_error("Cylinder axis not normalized"));
	if (cyl->diameter <= 0.0)
		return (mr_error("Cylinder diameter must be positive"));
	if (cyl->height <= 0.0)
		return (mr_error("Cylinder height must be positive"));
	return (1);
}

int	rt_parse_cylinder(char **tokens, t_cylinder *cyl)
{
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
		return (mr_error("Invalid cylinder format"));
	if (!tokens[4] || !tokens[5] || tokens[6])
		return (mr_error("Invalid cylinder format"));
	if (!mr_parse_vec3(tokens[1], &cyl->center))
		return (mr_error("Invalid cylinder center"));
	if (!mr_parse_vec3(tokens[2], &cyl->axis))
		return (mr_error("Invalid cylinder axis"));
	if (!mr_parse_float(tokens[3], &cyl->diameter))
		return (mr_error("Invalid cylinder diameter"));
	if (!mr_parse_float(tokens[4], &cyl->height))
		return (mr_error("Invalid cylinder height"));
	if (!mr_parse_color(tokens[5], &cyl->color))
		return (mr_error("Invalid cylinder color"));
	if (!mr_validate_cylinder_data(cyl))
		return (0);
	return (1);
}
