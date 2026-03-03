/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_select_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:30:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/03/03 18:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	rt_count_objs(void **objects)
{
	int	count;

	count = 0;
	if (!objects)
		return (0);
	while (objects[count])
		count++;
	return (count);
}

static void	rt_advance_selection(t_data *data, int n_sp, int n_cy)
{
	if (data->selected.type == SEL_NONE && n_sp > 0)
	{
		data->selected.type = SEL_SPHERE;
		data->selected.index = 0;
	}
	else if (data->selected.type == SEL_SPHERE)
	{
		if (data->selected.index + 1 < n_sp)
			data->selected.index++;
		else if (n_cy > 0)
		{
			data->selected.type = SEL_CYLINDER;
			data->selected.index = 0;
		}
		else
		{
			data->selected.type = SEL_NONE;
			data->selected.index = 0;
		}
	}
	else
		rt_advance_from_cyl(data, n_sp, n_cy);
}

void	rt_advance_from_cyl(t_data *data, int n_sp, int n_cy)
{
	if (data->selected.type == SEL_CYLINDER)
	{
		if (data->selected.index + 1 < n_cy)
			data->selected.index++;
		else
		{
			data->selected.type = SEL_NONE;
			data->selected.index = 0;
		}
	}
	else if (n_sp > 0)
	{
		data->selected.type = SEL_SPHERE;
		data->selected.index = 0;
	}
	else if (n_cy > 0)
	{
		data->selected.type = SEL_CYLINDER;
		data->selected.index = 0;
	}
	(void)n_sp;
}

int	rt_select_object(int keycode, t_data *data)
{
	int	n_sp;
	int	n_cy;

	if (keycode != KEY_TAB)
		return (0);
	n_sp = rt_count_objs((void **)data->scene.spheres);
	n_cy = rt_count_objs((void **)data->scene.cylinders);
	if (n_sp == 0 && n_cy == 0)
		return (0);
	rt_advance_selection(data, n_sp, n_cy);
	if (data->selected.type == SEL_SPHERE)
		ft_putendl_fd("Selected: sphere", 1);
	else if (data->selected.type == SEL_CYLINDER)
		ft_putendl_fd("Selected: cylinder", 1);
	else
		ft_putendl_fd("Selection cleared", 1);
	return (1);
}
