/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_handle_kpress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	rt_handle_kpress(int keycode, t_data *data)
{
	rt_destroy_on_esc(keycode, data);
	rt_select_object(keycode, data);
	rt_press_move_key(keycode, &data->keys);
	rt_press_resize_key(keycode, &data->keys);
	rt_press_rotate_key(keycode, &data->keys);
	return (0);
}
