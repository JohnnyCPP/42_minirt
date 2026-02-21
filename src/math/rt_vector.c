/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

double	rt_dotprod_of(t_coordinates v1, t_coordinates v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	rt_get_sqmag(t_coordinates v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	rt_get_mag(t_coordinates v)
{
	return (sqrt(rt_get_sqmag(v)));
}

t_coordinates	rt_add_vector(t_coordinates v1, t_coordinates v2)
{
	t_coordinates	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_coordinates	rt_subtract_vector(t_coordinates v1, t_coordinates v2)
{
	t_coordinates	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_coordinates	rt_multiply_vector(t_coordinates v, double scalar)
{
	t_coordinates	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_coordinates	rt_normalize_vector(t_coordinates v)
{
	t_coordinates	result;
	double			magnitude;

	magnitude = rt_get_sqmag(v);
	if (magnitude < EPSILON_SQ)
		return (v);
	magnitude = sqrt(magnitude);
	result.x = v.x / magnitude;
	result.y = v.y / magnitude;
	result.z = v.z / magnitude;
	return (result);
}

t_coordinates	rt_negate_vector(t_coordinates v)
{
	t_coordinates	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
