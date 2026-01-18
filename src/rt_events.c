/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		cleanup(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	handle_close(t_data *data)
{
	cleanup(data);
	exit(EXIT_SUCCESS);
	return (0);
}
