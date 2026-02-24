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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./miniRT <scene.rt>", 2);
		return (EXIT_ERROR);
	}
	if (!rt_parse_file(argv[1], &data.scene))
		return (EXIT_ERROR);
	if (rt_init(&data) == EXIT_ERROR)
	{
		ft_putendl_fd("Error: Failed to initialize window", 2);
		rt_free_scene(&data.scene);
		return (EXIT_ERROR);
	}
	rt_render(&data);
	mlx_hook(data.mlx.win, KeyPress, KeyPressMask, rt_h_kpress, &data);
	mlx_hook(data.mlx.win, DestroyNotify, StructureNotifyMask,
		rt_h_close, &data);
	mlx_loop(data.mlx.xvar);
	return (EXIT_SUCCESS);
}
