/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_h_kpress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		rt_free_scene(&data->scene);
		rt_destroy(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	rt_h_close(t_data *data)
{
	rt_free_scene(&data->scene);
	rt_destroy(data);
	exit(EXIT_SUCCESS);
	return (0);
}
