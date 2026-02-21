/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static	void	rt_destroy_mlx(t_minilib *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->xvar, mlx->img.img);
	if (mlx->win)
		mlx_destroy_window(mlx->xvar, mlx->win);
	if (mlx->xvar)
	{
		mlx_destroy_display(mlx->xvar);
		free(mlx->xvar);
	}
}

void	rt_destroy(t_data *data)
{
	rt_destroy_mlx(&data->mlx);
	rt_destroy_scene(&data->scene);
}
