/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:26:28 by igenez-y        ###   ########.fr       */
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
	data.selected.type = SEL_NONE;
	data.selected.index = 0;
	if (rt_init_mlx(&data.mlx) == EXIT_ERROR)
	{
		ft_putendl_fd("Error: Failed to initialize window", 2);
		rt_free_scene(&data.scene);
		return (EXIT_ERROR);
	}
	rt_configure_events(&data);
	rt_render(&data);
	mlx_loop_hook(data.mlx.xvar, rt_loop_hook, &data);
	mlx_loop(data.mlx.xvar);
	return (EXIT_SUCCESS);
}
