/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/23 10:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_check_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strcmp(&filename[len - 3], ".rt") != 0)
		return (rt_error("File must have .rt extension"));
	return (1);
}

static int	rt_validate_scene(t_scene *scene)
{
	(void)scene;
	// Basic validation - can be extended
	return (1);
}

static int	rt_read_and_parse(int fd, t_scene *scene)
{
	char	*line;
	int		ret;

	line = ft_gnl(fd);
	while (line)
	{
		ret = rt_parse_line(line, scene);
		free(line);
		if (!ret)
		{
			while (line)
			{
				line = ft_gnl(fd);
				free(line);
			}
			return (0);
		}
		line = ft_gnl(fd);
	}
	return (1);
}

int	rt_parse_file(char *filename, t_scene *scene)
{
	int	fd;

	if (!rt_check_extension(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (rt_error("Failed to open file"));
	ft_bzero(scene, sizeof(t_scene));
	if (!rt_read_and_parse(fd, scene))
	{
		close(fd);
		rt_free_scene(scene);
		return (0);
	}
	close(fd);
	if (!rt_validate_scene(scene))
	{
		rt_free_scene(scene);
		return (0);
	}
	return (1);
}
