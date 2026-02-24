/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:00:00 by jonnavar          #+#    #+#             */
/*   Updated: 2025/01/26 00:00:00 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_ambient(char **tokens, t_ambient *ambient)
{
	if (!tokens || !tokens[1] || !tokens[2] || tokens[3])
		return (rt_error("Invalid ambient format"));
	if (ambient->is_set)
		return (rt_error("Duplicate ambient lighting"));
	if (!rt_parse_float(tokens[1], &ambient->ratio))
		return (rt_error("Invalid ambient ratio"));
	if (!rt_validate_range(ambient->ratio, 0.0, 1.0))
		return (rt_error("Ambient ratio out of range [0.0,1.0]"));
	if (!rt_parse_color(tokens[2], &ambient->color))
		return (rt_error("Invalid ambient color"));
	ambient->is_set = 1;
	return (1);
}
