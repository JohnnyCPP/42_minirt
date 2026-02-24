/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 16:30:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_float(char *str, double *result)
{
	char	*endptr;
	double	value;

	if (!str || !result)
		return (0);
	value = rt_atof(str, &endptr);
	if (*endptr != '\0' && *endptr != ' ' && *endptr != '\t')
		return (0);
	*result = value;
	return (1);
}

int	rt_parse_vec3(char *str, t_coordinates *vec)
{
	char	**parts;
	int		ret;

	if (!str || !vec)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		rt_free_split(parts);
		return (0);
	}
	ret = rt_parse_float(parts[0], &vec->x);
	ret = ret && rt_parse_float(parts[1], &vec->y);
	ret = ret && rt_parse_float(parts[2], &vec->z);
	rt_free_split(parts);
	return (ret);
}

int	rt_parse_color(char *str, t_color *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (!str || !color)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		rt_free_split(parts);
		return (0);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	rt_free_split(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->red = r;
	color->green = g;
	color->blue = b;
	return (1);
}
