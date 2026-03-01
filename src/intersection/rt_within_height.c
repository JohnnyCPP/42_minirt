/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_within_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_within_height(double y, t_cylinder *cyl)
{
	return (fabs(y) <= cyl->half_height + EPSILON);
}
