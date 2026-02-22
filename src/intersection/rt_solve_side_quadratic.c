/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_solve_side_quadratic.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Solves quadratic for cylinder side intersection.
 *
 * In local coordinates, cylinder is x² + z² = r², infinite in y.
 */
int	rt_solve_side_quadratic(t_ray local, double r, double *t1, double *t2)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = local.direction.x * local.direction.x
		+ local.direction.z * local.direction.z;
	if (a < EPSILON)
		return (0);
	b = 2.0 * (local.origin.x * local.direction.x
			+ local.origin.z * local.direction.z);
	c = local.origin.x * local.origin.x
		+ local.origin.z * local.origin.z - r * r;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (0);
	*t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	*t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	return (1);
}
