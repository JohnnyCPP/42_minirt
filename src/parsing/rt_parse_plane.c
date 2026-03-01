/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/23 15:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_parse_plane(char **tokens, t_plane *plane)
{
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (rt_error("Invalid plane format"));
	if (!rt_parse_vec3(tokens[1], &plane->point))
		return (rt_error("Invalid plane point"));
	if (!rt_parse_vec3(tokens[2], &plane->orientation))
		return (rt_error("Invalid plane normal"));
	if (!rt_check_vec_range(plane->orientation, -1.0, 1.0))
		return (rt_error("Plane normal out of range [-1,1]"));
	if (!rt_validate_normalized(plane->orientation))
		return (rt_error("Plane normal is zero vector"));
	plane->orientation = rt_normalize_vector(plane->orientation);
	if (!rt_parse_color(tokens[3], &plane->color))
		return (rt_error("Invalid plane color"));
	return (1);
}
