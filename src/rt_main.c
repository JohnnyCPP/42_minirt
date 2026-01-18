/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static void	render_test_pattern(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = (x * 255 / WIN_WIDTH) << 16 | (y * 255 / WIN_HEIGHT) << 8;
			img_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (init_window(&data) == EXIT_ERROR)
	{
		ft_putendl_fd("Error: Failed to initialize window", 2);
		return (EXIT_ERROR);
	}
	render_test_pattern(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, handle_close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
