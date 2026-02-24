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

/**
 * @brief Initializes mock sphere data for testing before parser implementation.
 * 
 * Allocates and configures a single sphere with hardcoded values:
 * center(0,0,20.6), diameter 12.6, color(10,0,255)
 * 
 * @param scene Pointer to scene structure to populate with sphere data
 */
void	rt_mock_spheres(t_scene *scene);

/**
 * @brief Initializes mock plane data for testing before parser implementation.
 *
 * Allocates and configures a single plane with hardcoded values:
 * point(0,0,-10), normal(0,1,0), color(0,0,255)
 *
 * @param scene Pointer to scene structure to populate with plane data
 */
void	rt_mock_planes(t_scene *scene);

/**
 * @brief Initializes mock cylinder data 
 *        for testing before parser implementation.
 *
 * Allocates and configures a single cylinder with hardcoded values:
 * center(0,0,20.6), orientation(0,1,0), 
 * diameter 12.6, height 12.6, color(10,0,255)
 *
 * @param scene Pointer to scene structure to populate with cylinder data
 */
void	rt_mock_cylinders(t_scene *scene);

/**
 * @brief Initializes the MLX library, creates window, and sets up the scene.
 *
 * Creates MLX instance, window, and image buffer. Also initializes scene
 * with hardcoded values for testing.
 *
 * @param data Pointer to main data structure containing MLX and scene info
 * @return int EXIT_SUCCESS on success, EXIT_ERROR on failure
 */
int		rt_init(t_data *data);

/**
 * @brief Cleans up all allocated resources and destroys MLX objects.
 *
 * Frees all scene objects (spheres, planes, cylinders), destroys MLX image,
 * window, display, and frees the MLX instance.
 *
 * @param data Pointer to main data structure containing resources to free
 */
void	rt_destroy(t_data *data);

/**
 * @brief Frees all dynamically allocated scene objects.
 *
 * Iterates through spheres, planes, and cylinders arrays, freeing each
 * element and then the array itself.
 *
 * @param scene Pointer to scene structure containing object arrays to free
 */
void	rt_destroy_scene(t_scene *scene);

/**
 * @brief Handles keyboard press events.
 * 
 * Currently only handles ESC key to exit the program cleanly.
 * 
 * @param keycode The keycode of the pressed key
 * @param data Pointer to main data structure
 * @return int Always returns 0 to indicate event was processed
 */
int		rt_h_kpress(int keycode, t_data *data);

/**
 * @brief Handles window close button (red cross) events.
 *
 * Cleans up resources and exits the program when user clicks the close button.
 *
 * @param data Pointer to main data structure
 * @return int Always returns 0 (though function exits before return)
 */
int		rt_h_close(t_data *data);

/**
 * @brief Puts a single pixel at (x,y) coordinates in the image buffer.
 *
 * Performs bounds checking to ensure pixel is within window dimensions.
 * Uses MLX's image data addressing to write the color value.
 *
 * @param img Pointer to image structure containing buffer info
 * @param x X coordinate (0 to WIN_WIDTH-1)
 * @param y Y coordinate (0 to WIN_HEIGHT-1)
 * @param color RGB color value packed as integer (0x00RRGGBB)
 */
void	rt_put_pxl(t_img *img, int x, int y, int color);

// Parsing
int		rt_parse_file(char *filename, t_scene *scene);
int		rt_parse_line(char *line, t_scene *scene);
int		rt_parse_ambient(char **tokens, t_amb_light *ambient);
int		rt_parse_camera(char **tokens, t_camera *camera);
int		rt_parse_light(char **tokens, t_light *light);
int		rt_parse_sphere(char **tokens, t_sphere *sphere);
int		rt_parse_plane(char **tokens, t_plane *plane);
int		rt_parse_cylinder(char **tokens, t_cylinder *cyl);

// Parsing utilities
int		rt_parse_float(char *str, double *result);
int		rt_parse_vec3(char *str, t_coordinates *vec);
int		rt_parse_color(char *str, t_color *color);
int		rt_validate_normalized(t_coordinates vec);
int		rt_validate_range(double value, double min, double max);
int		rt_check_vec_range(t_coordinates vec, double min, double max);

// Object management
int		rt_add_sphere(t_scene *scene, t_sphere sphere);
int		rt_add_plane(t_scene *scene, t_plane plane);
int		rt_add_cylinder(t_scene *scene, t_cylinder cyl);

// Error handling
int		rt_error(char *message);
void	rt_free_scene(t_scene *scene);

// Utils
double	rt_atof(const char *str, char **endptr);
void	rt_free_split(char **split);
char	**rt_tokenize(char *str);

/**
 * @brief Computes the dot product of two vectors.
 * 
 * Dot product = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z
 * Used for projections, angles, and lighting calculations.
 * 
 * @param v1 First vector
 * @param v2 Second vector
 * @return double Dot product result
 */
double	rt_dotprod_of(t_coordinates v1, t_coordinates v2);

/**
 * @brief Computes the squared magnitude (length squared) of a vector.
 *
 * More efficient than rt_get_mag() when comparing distances without needing
 * the actual distance value, as it avoids the expensive sqrt operation.
 *
 * @param v Input vector
 * @return double Squared magnitude = x² + y² + z²
 */
double	rt_get_sqmag(t_coordinates v);

/**
 * @brief Computes the magnitude (length) of a vector.
 *
 * Uses sqrt(rt_get_sqmag(v)). For distance comparisons where exact
 * distance isn't needed, consider using rt_get_sqmag() for better performance.
 *
 * @param v Input vector
 * @return double Magnitude = √(x² + y² + z²)
 */
double	rt_get_mag(t_coordinates v);

/**
 * @brief Creates a ray from origin point in the specified direction.
 *
 * Automatically normalizes the direction vector to ensure unit length,
 * which simplifies intersection calculations.
 *
 * @param origin Starting point of the ray (camera position)
 * @param direction Direction vector (will be normalized)
 * @return t_ray Ray structure with origin and normalized direction
 */
t_ray	rt_create_ray(t_coordinates origin, t_coordinates direction);

/**
 * @brief Tests intersection between a ray and a sphere.
 *
 * Solves the quadratic equation at² + bt + c = 0 where:
 * a = D·D (ray direction dot itself, always 1 if normalized)
 * b = 2 * (O - C)·D
 * c = (O - C)·(O - C) - r²
 *
 * The discriminant determines if/how many intersections occur:
 * - < 0: No intersection
 * - = 0: Ray grazes sphere (tangent)
 * - > 0: Two intersections (entry and exit)
 *
 * @param ray The ray to test
 * @param sphere Pointer to sphere to test against
 * @param hit Pointer to hit structure to populate on intersection
 * @return int 1 if intersection occurred (and hit populated), 0 otherwise
 */
int		rt_intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);

/**
 * @brief Creates a ray from camera through a specific pixel.
 *
 * @param camera Camera structure
 * @param x Pixel x coordinate (0 to WIN_WIDTH-1)
 * @param y Pixel y coordinate (0 to WIN_HEIGHT-1)
 * @return t_ray Ray from camera through the specified pixel
 */
t_ray	rt_get_camera_ray(t_camera *camera, int x, int y);

/**
 * @brief Converts a t_color structure to an integer for MLX.
 *
 * MLX expects colors in 0x00RRGGBB format (big-endian RGB).
 *
 * @param color The color structure with red, green, blue components
 * @return int Packed color value (0x00RRGGBB)
 */
int		rt_get_color_int(t_color color);

/**
 * @brief Finds the closest sphere intersected by the ray.
 *
 * Iterates through all spheres in the scene, tests intersection,
 * and keeps the closest hit (smallest positive t value).
 *
 * @param ray The ray to test
 * @param scene Scene containing spheres array
 * @param hit Pointer to hit structure to populate with closest hit info
 * @return int 1 if any sphere was hit, 0 otherwise
 */
int		rt_find_closest_sphere(t_ray ray, t_scene *scene, t_hit *hit);

/**
 * @brief Finds the closest plane intersected by the ray.
 *
 * Iterates through all planes in the scene, tests intersection,
 * and keeps the closest hit (smallest positive t value).
 *
 * @param ray The ray to test
 * @param scene Scene containing planes array
 * @param hit Pointer to hit structure to populate with closest hit info
 * @return int 1 if any plane was hit, 0 otherwise
 */
int		rt_find_closest_plane(t_ray ray, t_scene *scene, t_hit *hit);

/**
 * @brief Finds the closest cylinder intersected by the ray.
 *
 * Iterates through all cylinders in the scene, tests intersection,
 * and keeps the closest hit (smallest positive t value).
 *
 * @param ray The ray to test
 * @param scene Scene containing cylinders array
 * @param hit Pointer to hit structure to populate with closest hit info
 * @return int 1 if any cylinder was hit, 0 otherwise
 */
int		rt_find_closest_cylinder(t_ray ray, t_scene *scene, t_hit *hit);

/**
 * @brief Finds the closest object (sphere, plane, or cylinder) hit by the ray.
 *
 * Tests all object types and keeps the closest intersection (smallest t).
 * This is the main intersection function called from the render loop.
 *
 * @param ray The ray to test
 * @param scene Scene containing all objects
 * @param hit Pointer to hit structure to populate with closest hit info
 * @return int 1 if any object was hit, 0 otherwise
 */
int		rt_find_closest_object(t_ray ray, t_scene *scene, t_hit *hit);

/**
 * @brief Renders the entire scene using ray tracing.
 *
 * Main render loop that iterates through all pixels, generates camera rays,
 * finds intersections, computes lighting, and draws pixels.
 *
 * @param data Main data structure containing MLX and scene info
 */
void	rt_render(t_data *data);

/**
 * @brief Tests intersection between a ray and a plane.
 *
 * Solves for t where (O + tD - P0) · n = 0
 * t = -((O - P0) · n) / (D · n)
 *
 * @param ray The ray to test
 * @param plane Pointer to plane to test against
 * @param hit Pointer to hit structure to populate on intersection
 * @return int 1 if intersection occurred (and hit populated), 0 otherwise
 */
int		rt_intersect_plane(t_ray ray, t_plane *plane, t_hit *hit);

/**
 * @brief Tests intersection between a ray and a cylinder.
 *
 * Handles both side intersection and cap intersections.
 * The cylinder is treated as an infinite cylinder first,
 * then clipped to the finite height.
 *
 * @param ray The ray to test
 * @param cylinder Pointer to cylinder to test against
 * @param hit Pointer to hit structure to populate on intersection
 * @return int 1 if intersection occurred (and hit populated), 0 otherwise
 */
int		rt_intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit);

void	rt_transform_ray(t_ray ray, t_cylinder *cyl, t_ray *local_ray);

int		rt_solve_side_quadratic(t_ray local, double r, double *t1, double *t2);

int		rt_within_height(double y, t_cylinder *cyl);

int		rt_intersect_caps(t_ray ray, t_cylinder *cyl, t_hit *hit);

#endif
