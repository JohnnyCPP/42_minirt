/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/23 15:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mr_parse_plane(char **tokens, t_plane *plane)
{
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (mr_error("Invalid plane format"));
	if (!mr_parse_vec3(tokens[1], &plane->point))
		return (mr_error("Invalid plane point"));
	if (!mr_parse_vec3(tokens[2], &plane->normal))
		return (mr_error("Invalid plane normal"));
	if (!mr_check_vec_range(plane->normal, -1.0, 1.0))
		return (mr_error("Plane normal out of range [-1,1]"));
	if (!mr_validate_normalized(plane->normal))
		return (mr_error("Plane normal not normalized"));
	if (!mr_parse_color(tokens[3], &plane->color))
		return (mr_error("Invalid plane color"));
	return (1);
}
