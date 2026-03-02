/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/02/24 12:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_STRUCTURES_H
# define MINIRT_STRUCTURES_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_minilib
{
	void	*xvar;
	void	*win;
	t_img	img;
}	t_minilib;

/**
 * rgb colors in the range [0,255]
 */
typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}	t_coordinates;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	direction;
}	t_ray;

typedef struct s_hit
{
	int				occurred;
	double			distance;
	t_coordinates	point;
	t_coordinates	normalized;
	t_color			color;
}	t_hit;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	t1;
	double	t2;
}	t_quadratic;

/**
 * @member ratio A value in the range [0.0,1.0]. 
 *               Represents how bright it is
 * @member color The color of the ambient lighting
 */
typedef struct s_amb_light
{
	double	ratio;
	t_color	color;
}	t_amb_light;

/**
 * @member viewpoint The camera location 
 * @member orientation Where the camera points to
 * @member fov Horizontal field of view in degrees.
 *             A value in the range [0,180]
 */
typedef struct s_camera
{
	t_coordinates	viewpoint;
	t_coordinates	orientation;
	int				fov;
}	t_camera;

/**
 * @member source The light location 
 * @member brightness A ratio in the range [0.0-1.0]
 * @member color The color of the light
 */
typedef struct s_light
{
	t_coordinates	source;
	double			brightness;
	t_color			color;
}	t_light;

/**
 * @member center The sphere location 
 * @member diameter The diameter of the sphere
 * @member color The color of the sphere
 */
typedef struct s_sphere
{
	t_coordinates	center;
	double			diameter;
	t_color			color;
	double			radius;
}	t_sphere;

/**
 * @member point A point in the plane 
 * @member orientation A 3D vector in the range [-1,1] for each x, y, and z 
 * @member color The color of the plane
 */
typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	orientation;
	t_color			color;
}	t_plane;

/**
 * @member center The cylinder location 
 * @member orientation A 3D vector in the range [-1,1] for each x, y, and z 
 * @member diameter The diameter of the cylinder
 * @member height The height of the cylinder
 * @member color The color of the cylinder
 */
typedef struct s_cylinder
{
	t_coordinates	center;
	t_coordinates	orientation;
	double			diameter;
	double			height;
	t_color			color;
	double			radius;
	double			half_height;
}	t_cylinder;

/**
 * @brief Digital description of a virtual world to be Rendered in a 2D surface.
 */
typedef struct s_scene
{
	t_amb_light	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;
	int			has_ambient;
	int			has_camera;
	int			has_light;
}	t_scene;

/**
 * @brief All data processed by the program, including MinilibX resources 
 *        and a scene description.
 */
typedef struct s_data
{
	t_minilib	mlx;
	t_scene		scene;
}	t_data;

/**
 * @brief Used during cylinder hit processing to avoid 
 *        passing more than 4 parameters
 */
typedef struct s_side_hit_aux
{
	t_ray		ray;
	t_cylinder	*cylinder;
	t_ray		local;
	double		t;
	double		t1;
	double		t2;
	t_hit		*hit;
}	t_side_hit_aux;

#endif
