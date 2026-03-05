/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_release_rotate_key.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/03/03 20:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	rt_release_rotate_key(int keycode, t_key_state *keys)
{
	if (keycode == KEY_UP)
		keys->up = 0;
	else if (keycode == KEY_DOWN)
		keys->down = 0;
	else if (keycode == KEY_LEFT)
		keys->left = 0;
	else if (keycode == KEY_RIGHT)
		keys->right = 0;
}
