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

static void	rt_test_pattern(t_data *data)
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
			rt_put_pxl(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./miniRT <scene.rt>", 2);
		return (EXIT_ERROR);
	}
	if (!mr_parse_file(argv[1], &data.scene))
		return (EXIT_ERROR);
	if (rt_init(&data) == EXIT_ERROR)
	{
		ft_putendl_fd("Error: Failed to initialize window", 2);
		mr_free_scene(&data.scene);
		return (EXIT_ERROR);
	}
	rt_test_pattern(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, rt_h_kpress, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, rt_h_close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
