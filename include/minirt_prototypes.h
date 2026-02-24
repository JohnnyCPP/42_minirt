/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/01/24 18:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_PROTOTYPES_H
# define MINIRT_PROTOTYPES_H

// Window management
int		rt_init(t_data *data);
void	rt_destroy(t_data *data);

// Event handlers
int		rt_h_kpress(int keycode, t_data *data);
int		rt_h_close(t_data *data);

// Image utilities
void	rt_put_pxl(t_img *img, int x, int y, int color);

// Parsing
int		rt_parse_file(char *filename, t_scene *scene);
int		rt_parse_line(char *line, t_scene *scene);
int		rt_parse_ambient(char **tokens, t_ambient *ambient);
int		rt_parse_camera(char **tokens, t_camera *camera);
int		rt_parse_light(char **tokens, t_light *light);
int		rt_parse_sphere(char **tokens, t_sphere *sphere);
int		rt_parse_plane(char **tokens, t_plane *plane);
int		rt_parse_cylinder(char **tokens, t_cylinder *cyl);

// Parsing utilities
int		rt_parse_float(char *str, double *result);
int		rt_parse_vec3(char *str, t_vec3 *vec);
int		rt_parse_color(char *str, t_color *color);
int		rt_validate_normalized(t_vec3 vec);
int		rt_validate_range(double value, double min, double max);
int		rt_check_vec_range(t_vec3 vec, double min, double max);

// Object management
int		rt_add_sphere(t_objects *objs, t_sphere sphere);
int		rt_add_plane(t_objects *objs, t_plane plane);
int		rt_add_cylinder(t_objects *objs, t_cylinder cyl);

// Error handling
int		rt_error(char *message);
void	rt_free_scene(t_scene *scene);

// Utils
double	rt_atof(const char *str, char **endptr);
void	rt_free_split(char **split);
char	**rt_tokenize(char *str);

#endif
