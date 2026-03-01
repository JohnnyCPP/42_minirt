/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/02/24 10:34:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/**
 * @brief Parses a single-element scene component (A, C, L).
 *
 * Handles elements that can only appear once in the scene:
 *     - A: Ambient lighting
 *     - C: Camera
 *     - L: Light
 *
 * Checks for duplicates using has_* flags in scene structure.
 *
 * @param tokens Tokenized line
 * @param scene Scene structure to populate
 * @return int 1 on success, 0 on failure, -1 if not an element
 */
static int	rt_parse_element(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)
	{
		if (scene->has_ambient)
			return (rt_error("Duplicate ambient lighting"));
		scene->has_ambient = 1;
		return (rt_parse_ambient(tokens, &scene->ambient));
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		if (scene->has_camera)
			return (rt_error("Duplicate camera"));
		scene->has_camera = 1;
		return (rt_parse_camera(tokens, &scene->camera));
	}
	else if (ft_strcmp(tokens[0], "L") == 0)
	{
		if (scene->has_light)
			return (rt_error("Duplicate light"));
		scene->has_light = 1;
		return (rt_parse_light(tokens, &scene->light));
	}
	return (-1);
}

/**
 * @brief Parses a multiple-instance object (sp, pl, cy).
 *
 * Handles objects that can appear multiple times:
 *     - sp: Sphere
 *     - pl: Plane
 *     - cy: Cylinder
 *
 * Creates temporary objects and adds them to scene arrays.
 *
 * @param tokens Tokenized line
 * @param scene Scene structure to populate
 * @return int 1 on success, 0 on failure
 */
static int	rt_parse_object(char **tokens, t_scene *scene)
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;

	if (ft_strcmp(tokens[0], "sp") == 0)
	{
		if (!rt_parse_sphere(tokens, &sp))
			return (0);
		return (rt_add_sphere(scene, sp));
	}
	else if (ft_strcmp(tokens[0], "pl") == 0)
	{
		if (!rt_parse_plane(tokens, &pl))
			return (0);
		return (rt_add_plane(scene, pl));
	}
	else if (ft_strcmp(tokens[0], "cy") == 0)
	{
		if (!rt_parse_cylinder(tokens, &cy))
			return (0);
		return (rt_add_cylinder(scene, cy));
	}
	return (rt_error("Unknown identifier"));
}

int	rt_parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		ret;

	if (!line || !scene || line[0] == '\0' || line[0] == '#')
		return (1);
	tokens = rt_tokenize(line);
	if (!tokens || !tokens[0])
	{
		rt_free_split(tokens);
		return (1);
	}
	ret = rt_parse_element(tokens, scene);
	if (ret == -1)
		ret = rt_parse_object(tokens, scene);
	rt_free_split(tokens);
	return (ret);
}
