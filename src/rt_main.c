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
	t_minilib	*mlx;
	int			x;
	int			y;
	int			color;

	mlx = &data->mlx;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = (x * 255 / WIN_WIDTH) << 16 | (y * 255 / WIN_HEIGHT) << 8;
			rt_put_pxl(&mlx->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	void	*window;

	(void)argc;
	(void)argv;
	if (rt_init(&data) == EXIT_ERROR)
	{
		ft_putendl_fd("Error: Failed to initialize window", 2);
		return (EXIT_ERROR);
	}
	rt_test_pattern(&data);
	window = data.mlx.win;
	mlx_hook(window, KeyPress, KeyPressMask, rt_h_kpress, &data);
	mlx_hook(window, DestroyNotify, StructureNotifyMask, rt_h_close, &data);
	mlx_loop(data.mlx.xvar);
	return (EXIT_SUCCESS);
}
