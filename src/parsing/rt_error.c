/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 00:00:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/27 00:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	if (message)
		ft_putendl_fd(message, 2);
	return (0);
}

void	rt_free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->objects.spheres)
		free(scene->objects.spheres);
	if (scene->objects.planes)
		free(scene->objects.planes);
	if (scene->objects.cylinders)
		free(scene->objects.cylinders);
	ft_bzero(scene, sizeof(t_scene));
}
