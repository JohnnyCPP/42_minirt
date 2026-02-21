/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_PROTOTYPES_H
# define MINIRT_PROTOTYPES_H

// Testing
void	rt_mock_spheres(t_scene *scene);
void	rt_mock_planes(t_scene *scene);
void	rt_mock_cylinders(t_scene *scene);

// Window management
int		rt_init(t_data *data);
void	rt_destroy(t_data *data);
void	rt_destroy_scene(t_scene *scene);

// Event handlers
int		rt_h_kpress(int keycode, t_data *data);
int		rt_h_close(t_data *data);

// Image utilities
void	rt_put_pxl(t_img *img, int x, int y, int color);

#endif
