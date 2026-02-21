/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_negate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_coordinates	rt_negate_vector(t_coordinates v)
{
	t_coordinates	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
