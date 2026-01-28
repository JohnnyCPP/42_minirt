/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_parse_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mr_validate_normalized(t_vec3 vec)
{
	// to be implemented, euclidean length check

}

int	mr_validate_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	mr_check_vec_range(t_vec3 vec, double min, double max)
{
	if (!mr_validate_range(vec.x, min, max))
		return (0);
	if (!mr_validate_range(vec.y, min, max))
		return (0);
	if (!mr_validate_range(vec.z, min, max))
		return (0);
	return (1);
}
