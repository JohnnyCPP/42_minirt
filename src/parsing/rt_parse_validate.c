/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_validate_normalized(t_coordinates vec)
{
	double	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length < EPSILON_INTSEC)
		return (0);
	return (1);

}

int	rt_validate_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	rt_check_vec_range(t_coordinates vec, double min, double max)
{
	if (!rt_validate_range(vec.x, min, max))
		return (0);
	if (!rt_validate_range(vec.y, min, max))
		return (0);
	if (!rt_validate_range(vec.z, min, max))
		return (0);
	return (1);
}
