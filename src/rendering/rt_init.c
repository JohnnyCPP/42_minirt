/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (EXIT_ERROR);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->win)
	{
		free(data->mlx);
		return (EXIT_ERROR);
	}
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		return (EXIT_ERROR);
	}
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	return (EXIT_SUCCESS);
}
