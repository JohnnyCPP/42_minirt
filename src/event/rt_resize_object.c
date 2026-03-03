/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resize_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:00:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/03/03 18:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	rt_resize_sphere(t_sphere *sp, double step)
{
	if (sp->diameter + step <= EPSILON)
		return (0);
	sp->diameter += step;
	sp->radius = sp->diameter / 2.0;
	return (1);
}

static int	rt_resize_cyl_diam(t_cylinder *cyl, double step)
{
	if (cyl->diameter + step <= EPSILON)
		return (0);
	cyl->diameter += step;
	cyl->radius = cyl->diameter / 2.0;
	return (1);
}

static int	rt_resize_cyl_height(t_cylinder *cyl, double step)
{
	if (cyl->height + step <= EPSILON)
		return (0);
	cyl->height += step;
	cyl->half_height = cyl->height / 2.0;
	return (1);
}

int	rt_resize_diameter(int keycode, t_data *data)
{
	double	step;

	if (keycode != KEY_PLUS && keycode != KEY_MINUS)
		return (0);
	if (data->selected.type == SEL_NONE)
		return (0);
	step = RESIZE_STEP;
	if (keycode == KEY_MINUS)
		step = -RESIZE_STEP;
	if (data->selected.type == SEL_SPHERE)
		return (rt_resize_sphere(
				data->scene.spheres[data->selected.index], step));
	if (data->selected.type == SEL_CYLINDER)
		return (rt_resize_cyl_diam(
				data->scene.cylinders[data->selected.index], step));
	return (0);
}

int	rt_resize_height(int keycode, t_data *data)
{
	double	step;

	if (keycode != KEY_RBRACKET && keycode != KEY_LBRACKET)
		return (0);
	if (data->selected.type != SEL_CYLINDER)
		return (0);
	step = RESIZE_STEP;
	if (keycode == KEY_LBRACKET)
		step = -RESIZE_STEP;
	return (rt_resize_cyl_height(
			data->scene.cylinders[data->selected.index], step));
}
