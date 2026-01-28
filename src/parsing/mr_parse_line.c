#include "minirt.h"

static int	mr_parse_element(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)
		return (mr_parse_ambient(tokens, &scene->ambient));
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (mr_parse_camera(tokens, &scene->camera));
	else if (ft_strcmp(tokens[0], "L") == 0)
		return (mr_parse_light(tokens, &scene->light));
	return (-1);
}

static int	mr_parse_object(char **tokens, t_scene *scene)
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;

	if (ft_strcmp(tokens[0], "sp") == 0)
	{
		if (!mr_parse_sphere(tokens, &sp))
			return (0);
		return (mr_add_sphere(&scene->objects, sp));
	}
	else if (ft_strcmp(tokens[0], "pl") == 0)
	{
		if (!mr_parse_plane(tokens, &pl))
			return (0);
		return (mr_add_plane(&scene->objects, pl));
	}
	else if (ft_strcmp(tokens[0], "cy") == 0)
	{
		if (!mr_parse_cylinder(tokens, &cy))
			return (0);
		return (mr_add_cylinder(&scene->objects, cy));
	}
	return (mr_error("Unknown identifier"));
}

int	mr_parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		ret;

	if (!line || !scene || line[0] == '\0' || line[0] == '#')
		return (1);
	tokens = mr_tokenize(line);
	if (!tokens || !tokens[0])
	{
		mr_free_split(tokens);
		return (1);
	}
	ret = mr_parse_element(tokens, scene);
	if (ret == -1)
		ret = mr_parse_object(tokens, scene);
	mr_free_split(tokens);
	return (ret);
}
