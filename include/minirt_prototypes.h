/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2026/02/24 12:00:00 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_PROTOTYPES_H
# define MINIRT_PROTOTYPES_H

/**
 * @brief Initializes the MLX library, creates window, and sets up the scene.
 *
 * Creates MLX instance, window, and image buffer.
 *
 * @param data Pointer to structure containing MLX and scene info
 * @return int EXIT_SUCCESS on success, EXIT_ERROR on failure
 */
int		rt_init_mlx(t_minilib *mlx);

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
 * @brief Checks for ESC key press and performs cleanup if detected.
 *
 * This function is called during keyboard event handling to check if the
 * ESC key has been pressed. If so, it triggers the complete destruction
 * of all program resources and exits gracefully. This ensures that no
 * memory leaks occur when the user quits the program.
 */
void	rt_destroy_on_esc(int keycode, t_data *data);

/**
 * @brief Handles forward/backward camera movement from keyboard input.
 *
 * Processes W and S key presses to move the camera along its viewing direction.
 * Forward movement (W) translates the camera in the direction of its
 * orientation vector. Backward movement (S) translates in
 * the opposite direction.
 *
 * Movement visualization:
 *
 *                    Forward (W)
 *                        ↑
 *                        |
 *                        |
 *     Camera ●───────────┼───────────► View direction
 *                        |
 *                        |
 *                        ↓
 *                    Backward (S)
 *
 * @param keycode The X11 keycode of the pressed key
 * @param data Pointer to the main program data structure containing
 *             the camera to be moved
 * @return int 1 if a movement was performed (W or S pressed),
 *             0 otherwise (no action taken)
 *
 * @note The movement speed is determined by CAM_MOV_SPEED constant
 * @note This function only handles the key detection; actual movement
 *       is delegated to rt_move_camera_forward/backward
 *
 * @see rt_move_camera_forward
 * @see rt_move_camera_backward
 * @see CAM_MOV_SPEED defined in minirt_constants.h
 */
int		rt_move_camera_forw_backw(int keycode, t_data *data);

/**
 * @brief Handles left/right strafing camera movement from keyboard input.
 *
 * Processes A and D key presses to move the camera perpendicular to its
 * viewing direction (strafing). Left movement (A) translates along the
 * negative camera right vector. Right movement (D) translates along the
 * positive camera right vector.
 *
 * Movement visualization (top-down view):
 *
 *         Left (A)          Right (D)
 *           ←                 →
 *           │                 │
 *           └──────●──────────┘
 *                Camera
 *                  ↑
 *              Forward (into screen)
 *
 * @param keycode The X11 keycode of the pressed key
 * @param data Pointer to the main program data structure containing
 *             the camera to be moved
 * @return int 1 if a movement was performed (A or D pressed),
 *             0 otherwise (no action taken)
 *
 * @note The camera's right vector is computed from its orientation
 *       using the cross product with the world up vector
 * @note Strafing maintains the camera's viewing direction while
 *       moving sideways, useful for positioning shots
 *
 * @see rt_get_camera_right for right vector calculation
 * @see rt_move_camera_left
 * @see rt_move_camera_right
 */
int		rt_move_camera_left_right(int keycode, t_data *data);

/**
 * @brief Handles vertical camera movement from keyboard input.
 *
 * Processes SPACE and LEFT CTRL key presses to move the camera along its
 * local up vector. This creates an intuitive "flying" movement where
 * up always means "toward the top of the screen" regardless of camera
 * orientation. When the camera is pitched down, moving up will lift the
 * camera relative to its tilted view.
 *
 * Movement visualization:
 *
 *     Without pitch:            With pitch down:
 *
 *         Up (SPACE)                 Up (SPACE)
 *            ↑                          ↗
 *            |                         /
 *            |                        /
 *     ●──────┼──────►            ●───┼──────►
 *   Camera   | Forward         Camera  Forward
 *            |                        \
 *            ↓                          ↘
 *      Down (CTRL)                  Down (CTRL)
 *
 * @param keycode The X11 keycode of the pressed key
 * @param data Pointer to the main program data structure containing
 *             the camera to be moved
 * @return int 1 if a movement was performed (SPACE or LEFT CTRL pressed),
 *             0 otherwise (no action taken)
 *
 * @note Using SPACE and CTRL for vertical movement follows common
 *       3D software conventions (Blender, CAD tools, etc.)
 * @note The up vector is computed from the camera's orientation and
 *       right vector, ensuring it's always perpendicular to the view
 *
 * @see rt_get_camera_up for up vector calculation
 * @see rt_move_camera_up
 * @see rt_move_camera_down
 */
int		rt_move_camera_up_down(int keycode, t_data *data);

/**
 * @brief Handles camera rotation from arrow key input.
 *
 * Processes arrow key presses to rotate the camera's orientation:
 *     - UP/DOWN: Pitch rotation (look up/down) around the camera's right axis
 *     - LEFT/RIGHT: Yaw rotation (look left/right) around the world up axis
 *
 * Rotation visualization:
 *
 *                    Yaw (LEFT/RIGHT)
 *                 ←─────────●─────────→
 *                          /|\
 *                           |
 *                     Pitch (UP/DOWN)
 *
 * The camera uses axis-angle rotation (Rodrigues' formula) for smooth,
 * gimbal-lock-free rotation:
 *     - Pitch rotates around the camera's local right vector
 *     - Yaw rotates around the world Y axis to maintain horizon level
 *
 * @param keycode The X11 keycode of the pressed key
 * @param data Pointer to the main program data structure containing
 *             the camera to be rotated
 * @return int 1 if a rotation was performed (arrow key pressed),
 *             0 otherwise (no action taken)
 *
 * @note Rotation speed is determined by CAM_ROT_SPEED constant (radians)
 * @note Pitch is limited only by floating-point precision; the camera
 *       can look straight up or down without issue
 * @note The orientation vector is automatically renormalized after
 *       each rotation to maintain unit length
 *
 * @see rt_pitch_camera for pitch rotation implementation
 * @see rt_yaw_camera for yaw rotation implementation
 * @see rt_rotate_axis for the underlying Rodrigues' rotation formula
 */
int		rt_rotate_camera_event(int keycode, t_data *data);

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

/**
 * @brief Computes the final lighting color at a hit point using Phong model.
 *
 * Combines ambient and diffuse lighting components with shadow handling
 * to produce the final pixel color.
 *
 * The lighting computation follows this decision tree:
 *
 *                    Hit point
 *                        |
 *            ┌───────────┴───────────┐
 *            ↓                        ↓
 *     Ambient lighting          Diffuse lighting
 *     (always present)          (if surface faces light)
 *            ↓                        ↓
 *     base_color * 0.2      color * (n·l) * brightness
 *            ↓                        ↓
 *            └───────────┬─────────────┘
 *                        ↓
 *                 Is point in shadow?
 *                        ↓
 *            ┌───────────┴───────────┐
 *            ↓                        ↓
 *          Yes                        No
 *            ↓                        ↓
 *     Return ambient only       Return ambient + diffuse
 *
 * @param scene Pointer to scene containing ambient light and light source
 * @param hit The hit point data (position, normal, object color)
 * @return t_color Final color after all lighting calculations
 *
 * @note Special cases handled:
 *       - If diffuse contribution is zero (surface facing away),
 *         returns only ambient
 *       - If point is in shadow, returns only ambient (no diffuse)
 *       - Final color components are clamped to [0, 255]
 *
 * @see rt_compute_diffuse for diffuse calculation details
 * @see rt_is_in_shadow for shadow determination
 * @see rt_clamp for color component clamping
 *
 * @warning This implements the mandatory part only (ambient + diffuse).
 *          Specular and other lighting effects are not included.
 */
t_color	rt_compute_lighting(t_scene *scene, t_hit hit);

/**
 * @brief Main file parsing function - reads and validates .rt scene file.
 *
 * Complete parsing workflow:
 *
 *     filename
 *         ↓
 *     Check .rt extension ──Fail──► Error
 *         ↓ Pass
 *     Open file ───────────Fail──► Error
 *         ↓ Pass
 *     Initialize scene (zero)
 *         ↓
 *     Read and parse all lines ──Fail──► Close file, free scene, error
 *         ↓ Success
 *     Close file
 *         ↓
 *     Validate required elements ──Fail──► Free scene, error
 *         ↓ Pass
 *     Return success
 *
 * @param filename Path to .rt scene file
 * @param scene Output parameter for parsed scene
 * @return int 1 on success, 0 on failure
 *
 * @note On failure, scene is automatically freed and zeroed
 * @note Memory leaks are prevented by proper cleanup in error paths
 */
int		rt_parse_file(char *filename, t_scene *scene);

/**
 * @brief Parses a single line from the scene file.
 *
 * Main line parsing function that:
 *     1. Skips empty lines and comments
 *     2. Tokenizes the line
 *     3. Routes to appropriate parser based on identifier
 *
 * Line processing flow:
 *
 *     Raw line
 *         ↓
 *     Empty or comment? ──Yes──► Return 1 (skip)
 *         ↓ No
 *     Tokenize
 *         ↓
 *     Parse element (A/C/L)? ──Yes──► Validate duplicate, parse
 *         ↓ No                      ↓
 *     Parse object (sp/pl/cy)? ──Yes──► Parse and add to scene
 *         ↓ No                      ↓
 *     Unknown identifier ──────────► Error
 *
 * @param line Raw line from scene file
 * @param scene Scene structure to populate
 * @return int 1 on success, 0 on failure
 */
int		rt_parse_line(char *line, t_scene *scene);

/**
 * @brief Parses ambient lighting definition from tokenized line.
 *
 * Expected format:
 *     A  ratio  color
 *     ↓  ↓      ↓
 *     [0] [1]   [2]
 *
 * Example:
 *     A  0.2  255,255,255
 *
 * Parsing steps:
 *     1. Validate token count (exactly 3 tokens)
 *     2. Parse ratio
 *     3. Validate ratio in range [0.0, 1.0]
 *     4. Parse color
 *
 * Validation ensures:
 *     - Ratio between 0.0 and 1.0 (inclusive)
 *     - Color components within [0, 255]
 *
 * @param tokens Array of tokens from the parsed line
 * @param ambient Output parameter for parsed ambient light
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note Ambient lighting is a single declaration in the scene file
 * @see rt_validate_range for ratio validation
 */
int		rt_parse_ambient(char **tokens, t_amb_light *ambient);

/**
 * @brief Parses a camera definition from tokenized line.
 *
 * Expected format:
 *     C  viewpoint  orientation  FOV
 *     ↓  ↓          ↓            ↓
 *     [0] [1]       [2]          [3]
 *
 * Example:
 *     C  -50,0,20  0,0,1  70
 *
 * Parsing steps:
 *     1. Validate token count (exactly 4 tokens)
 *     2. Parse viewpoint position
 *     3. Parse orientation vector
 *     4. Validate orientation components in range [-1, 1]
 *     5. Validate orientation is not zero vector
 *     6. Normalize orientation
 *     7. Parse and validate FOV in range [0, 180]
 *
 * Validation ensures:
 *     - Orientation components within [-1, 1]
 *     - Orientation has non-zero length
 *     - FOV is integer between 0 and 180 degrees
 *
 * @param tokens Array of tokens from the parsed line
 * @param camera Output parameter for parsed camera
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note The orientation is normalized to ensure unit length
 *       for consistent ray generation.
 */
int		rt_parse_camera(char **tokens, t_camera *camera);

/**
 * @brief Parses a light definition from tokenized line.
 *
 * Expected format:
 *     L  position  brightness  [color]
 *     ↓   ↓        ↓            ↓
 *     [0] [1]      [2]          [3] (optional)
 *
 * Example:
 *     L  -40,0,30  0.7  255,255,255
 *
 * Parsing steps:
 *     1. Validate minimum token count (at least 3)
 *     2. Parse position
 *     3. Parse brightness
 *     4. Validate brightness in range [0.0, 1.0]
 *     5. Parse color (or use default white)
 *
 * @param tokens Array of tokens from the parsed line
 * @param light Output parameter for parsed light
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note Color is optional per subject, defaults to white
 */
int		rt_parse_light(char **tokens, t_light *light);

/**
 * @brief Parses a sphere definition from tokenized line.
 *
 * Expected format:
 *     sp  center  diameter  color
 *     ↓   ↓       ↓         ↓
 *     [0] [1]     [2]       [3]
 *
 * Example:
 *     sp  0,0,20.6  12.6  255,0,0
 *
 * Parsing steps:
 *     1. Validate token count (exactly 4 tokens)
 *     2. Parse center coordinates
 *     3. Parse diameter
 *     4. Validate diameter positive
 *     5. Parse color
 *
 * Validation ensures:
 *     - Diameter > 0 (physical object must have size)
 *     - Color components within [0, 255]
 *
 * @param tokens Array of tokens from the parsed line
 * @param sphere Output parameter for parsed sphere
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note Unlike cylinders, spheres don't need pre-computed values
 *       as radius is calculated on-the-fly during intersection.
 */
int		rt_parse_sphere(char **tokens, t_sphere *sphere);

/**
 * @brief Parses a plane definition from tokenized line.
 *
 * Expected format:
 *     pl  point  normal  color
 *     ↓   ↓      ↓       ↓
 *     [0] [1]    [2]     [3]
 *
 * Example:
 *     pl  0,0,0  0,1,0  0,255,0
 *
 * Parsing steps:
 *     1. Validate token count (exactly 4 tokens)
 *     2. Parse point on plane
 *     3. Parse normal vector
 *     4. Validate normal components in range [-1, 1]
 *     5. Validate normal is not zero vector
 *     6. Normalize normal vector
 *     7. Parse color
 *
 * Validation ensures:
 *     - Normal vector components are within [-1, 1]
 *     - Normal vector has non-zero length
 *     - Color components within [0, 255]
 *
 * @param tokens Array of tokens from the parsed line
 * @param plane Output parameter for parsed plane
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note The normal vector is automatically normalized after validation
 *       to ensure unit length for intersection calculations.
 */
int		rt_parse_plane(char **tokens, t_plane *plane);

/**
 * @brief Parses a cylinder definition from tokenized line.
 *
 * Expected format:
 *     cy  center  axis  diameter  height  color
 *     ↓   ↓       ↓     ↓         ↓       ↓
 *     [0] [1]     [2]   [3]       [4]     [5]
 *
 * Example:
 *     cy  0,0,20.6  0,0,1  14.2  21.42  10,0,255
 *
 * Parsing steps:
 *     1. Validate token count (exactly 6 tokens)
 *     2. Parse center vector
 *     3. Parse axis orientation vector
 *     4. Parse diameter
 *     5. Parse height
 *     6. Parse color
 *     7. Validate semantic constraints
 *     8. Pre-compute radius and half_height
 *
 * @param tokens Array of tokens from the parsed line
 * @param cyl Output parameter for parsed cylinder
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @see rt_validate_cylinder_data for post-parse validation
 */
int		rt_parse_cylinder(char **tokens, t_cylinder *cyl);

/**
 * @brief Parses a floating-point number from a string.
 *
 * Wrapper around rt_atof that validates the entire string was consumed.
 * Ensures there are no extra characters after the number (except whitespace).
 *
 * Parsing examples:
 *     "42.5"   → OK (endptr at '\0')
 *     "42.5 "  → OK (endptr at space, allowed)
 *     "42.5x"  → FAIL (endptr at 'x', not allowed)
 *
 * @param str String to parse (expected to contain a float)
 * @param result Output parameter for the parsed value
 * @return int 1 on success, 0 on failure
 *
 * @note Used extensively throughout parsing for numeric values
 * @see rt_atof for the actual conversion
 */
int		rt_parse_float(char *str, double *result);

/**
 * @brief Parses a 3D vector from a comma-separated string.
 *
 * Format expected: "x,y,z" where each component is a floating-point number.
 *
 * Parsing flow:
 *     Input: "1.5,-2.0,3.7"
 *            ↓       ↓    ↓
 *     Split: ["1.5", "-2.0", "3.7", NULL]
 *              ↓      ↓       ↓
 *            parse  parse   parse
 *              ↓      ↓       ↓
 *            vec.x  vec.y   vec.z
 *
 * Validation ensures:
 *     - Exactly three components (no more, no less)
 *     - Each component is a valid float
 *     - No extra trailing data
 *
 * @param str The comma-separated vector string
 * @param vec Output parameter for parsed coordinates
 * @return int 1 on success, 0 on failure
 *
 * @note The input string is not modified
 * @note Memory for split parts is automatically freed
 */
int		rt_parse_vec3(char *str, t_coordinates *vec);

/**
 * @brief Parses an RGB color from a comma-separated string.
 *
 * Format expected: "r,g,b" where each component is an integer 0-255.
 *
 * Parsing flow:
 *     Input: "255,128,0"
 *            ↓    ↓   ↓
 *     Split: ["255", "128", "0", NULL]
 *              ↓     ↓     ↓
 *            atoi   atoi  atoi
 *              ↓     ↓     ↓
 *            red=255 g=128 b=0
 *
 * Validation ensures:
 *     - Exactly three components
 *     - Each component is a valid integer
 *     - Each component is in range [0, 255]
 *
 * @param str The comma-separated color string
 * @param color Output parameter for parsed color
 * @return int 1 on success, 0 on failure
 */
int		rt_parse_color(char *str, t_color *color);

/**
 * @brief Validates that a vector has non-zero length (can be normalized).
 *
 * Checks if a vector can be used as a valid direction/orientation vector.
 * A zero vector would cause division by zero during normalization.
 *
 * Validation criteria:
 *     - sqrt(x² + y² + z²) > EPSILON_INTSEC
 *
 * @param vec The vector to validate
 * @return int 1 if vector length > EPSILON_INTSEC, 0 otherwise
 *
 * @note Uses EPSILON_INTSEC (1e-6) as threshold to handle floating-point
 *       precision issues with near-zero vectors.
 *
 * @see EPSILON_INTSEC defined in minirt_constants.h
 */
int		rt_validate_normalized(t_coordinates vec);

/**
 * @brief Validates that a scalar value is within specified range [min, max].
 *
 * Used throughout parsing to ensure values like light brightness,
 * ambient ratio, etc., conform to .rt file format specifications.
 *
 * @param value The value to validate
 * @param min Minimum allowed value (inclusive)
 * @param max Maximum allowed value (inclusive)
 * @return int 1 if min ≤ value ≤ max, 0 otherwise
 */
int		rt_validate_range(double value, double min, double max);

/**
 * @brief Validates that all components of a vector are within specified range.
 *
 * Convenience wrapper around rt_validate_range for vectors.
 * Ensures each coordinate satisfies x,y,z ∈ [min, max].
 *
 * Used primarily for:
 *     - Camera orientation vectors (must be in [-1, 1])
 *     - Plane normal vectors (must be in [-1, 1])
 *     - Cylinder axis vectors (must be in [-1, 1])
 *
 * @param vec The vector to validate
 * @param min Minimum allowed value for each component
 * @param max Maximum allowed value for each component
 * @return int 1 if all components are in range, 0 otherwise
 *
 * @see rt_validate_range for component validation
 */
int		rt_check_vec_range(t_coordinates vec, double min, double max);

/**
 * @brief Adds a new sphere to the scene's sphere array.
 *
 * Dynamic array management for spheres:
 *     1. Count existing spheres
 *     2. Allocate new array with space for one more + NULL terminator
 *     3. Create new sphere object
 *     4. Copy existing sphere pointers
 *     5. Add new sphere at the end
 *     6. NULL-terminate the array
 *     7. Free old array and update scene pointer
 *
 * Memory management visualization:
 *
 *     Before:
 *     scene->spheres ──► [sp0][sp1][NULL]
 *
 *     After adding sphere sp2:
 *                         ┌─ sp0 ─┐
 *                         │  sp1  │
 *     scene->spheres ──► [├─ sp2 ─┤][NULL]  (new array)
 *                         └─ ... ─┘
 *     Old array freed
 *
 * @param scene Scene structure to modify
 * @param sphere Sphere data to add (will be copied to heap)
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note The sphere parameter is passed by value (stack) and copied to heap
 * @note The array is always NULL-terminated for easy iteration
 * @see rt_new_sp for sphere allocation
 * @see rt_copy_spheres for pointer preservation
 */
int		rt_add_sphere(t_scene *scene, t_sphere sphere);

/**
 * @brief Adds a new plane to the scene's plane array.
 *
 * Dynamic array management for planes following the same pattern as spheres.
 * Implements the classic dynamic array growth strategy:
 *     size_new = size_old + 1
 *
 * Array state transition:
 *
 *     Step 1: Count current planes
 *     scene->planes ──► [pl0][pl1][NULL]  (count = 2)
 *
 *     Step 2: Allocate new array (count + 2 slots)
 *     new_array ──► [  ][  ][  ][NULL]
 *                    ↑   ↑   ↑
 *                  slot0|slot1|slot2 (for new plane)
 *
 *     Step 3: Copy existing pointers and add new plane
 *     new_array ──► [pl0][pl1][new][NULL]
 *
 *     Step 4: Free old array, update scene pointer
 *
 * @param scene Scene structure to modify
 * @param plane Plane data to add (will be copied to heap)
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note Memory leak prevention: old array is freed only after successful
 *       allocation and copying of all data
 */
int		rt_add_plane(t_scene *scene, t_plane plane);

/**
 * @brief Adds a new cylinder to the scene's cylinder array.
 *
 * Implements the same dynamic array pattern as spheres and planes,
 * ensuring consistent memory management across all object types.
 *
 * Complete reallocation process:
 *
 *     ┌─────────────────────────────────────┐
 *     │      Add Cylinder to Scene          │
 *     └─────────────────────────────────────┘
 *                        │
 *                        ↓
 *     ┌─────────────────────────────────────┐
 *     │ count = current cylinders           │
 *     │ e.g., 2 cylinders: [c0][c1][NULL]  │
 *     └─────────────────────────────────────┘
 *                        │
 *                        ↓
 *     ┌─────────────────────────────────────┐
 *     │ Allocate (count + 2) * pointer size │
 *     │ New array: [   ][   ][   ][NULL]    │
 *     │             ↑    ↑    ↑              │
 *     │            old  old  new cylinder    │
 *     └─────────────────────────────────────┘
 *                        │
 *                        ↓
 *     ┌─────────────────────────────────────┐
 *     │ Create new cylinder on heap         │
 *     │ Copy data: center, orientation,     │
 *     │           diameter, height, color,  │
 *     │           radius, half_height       │
 *     └─────────────────────────────────────┘
 *                        │
 *                        ↓
 *     ┌─────────────────────────────────────┐
 *     │ Copy old pointers to new array      │
 *     │ Add new cylinder at the end         │
 *     │ NULL-terminate array                │
 *     └─────────────────────────────────────┘
 *                        │
 *                        ↓
 *     ┌─────────────────────────────────────┐
 *     │ Free old array                      │
 *     │ Update scene->cylinders             │
 *     └─────────────────────────────────────┘
 *
 * @param scene Scene structure to modify
 * @param cylinder Cylinder data to add (will be copied to heap)
 * @return int 1 on success, 0 on failure (with error message)
 *
 * @note Pre-computed values (radius, half_height) are part of the
 *       cylinder structure and are preserved during copying
 * @see rt_new_cyl for cylinder allocation
 * @see rt_copy_cylinders for pointer preservation
 */
int		rt_add_cylinder(t_scene *scene, t_cylinder cyl);

/**
 * @brief Prints an error message to stderr and returns failure.
 *
 * Standard error reporting function for the miniRT project.
 * Always prints "Error\n" followed by an optional custom message.
 * Used throughout parsing and initialization to provide consistent
 * error feedback to the user.
 *
 * Output format:
 *     Error
 *     [message]   (if message is not NULL)
 *
 * Example usage:
 *     if (rt_validate_range(value, 0, 1))
 *         return (rt_error("Light ratio must be between 0 and 1"));
 *
 *     stderr output:
 *     Error
 *     Light ratio must be between 0 and 1
 *
 * @param message Optional error description (can be NULL)
 * @return int Always returns 0 for convenient error return pattern:
 *            "return (rt_error("message"));"
 *
 * @note The function returns 0 to allow easy integration with
 *       functions that expect to return 0 on failure.
 */
int		rt_error(char *message);

/**
 * @brief Frees all dynamically allocated memory in a scene structure.
 *
 * Comprehensive cleanup function that:
 *     1. Frees all spheres array and individual spheres
 *     2. Frees all planes array and individual planes
 *     3. Frees all cylinders array and individual cylinders
 *     4. Zeroes out the entire scene structure
 *
 * Memory layout cleanup:
 *
 *     scene ──► spheres ──► [0] ──► sphere0
 *     (zeroed)    │         [1] ──► sphere1
 *                 │         [2] ──► sphere2
 *                 │         [3] ──► NULL
 *                 │
 *                 ├── planes ──► [0] ──► plane0
 *                 │              [1] ──► plane1
 *                 │              [2] ──► NULL
 *                 │
 *                 └── cylinders ─► [0] ──► cylinder0
 *                                  [1] ──► NULL
 *
 *     After rt_free_scene:
 *     All individual objects freed, all arrays freed,
 *     scene structure zeroed (all pointers NULL)
 *
 * @param scene Pointer to scene structure to free
 *
 * @note This function safely handles NULL pointers and partial arrays
 * @note After calling this, the scene structure should not be used
 *       without reinitialization
 * @note Part of the mandatory memory management requirements
 *
 * @see rt_free_scene_spheres
 * @see rt_free_scene_planes
 * @see rt_free_scene_cylinders
 */
void	rt_free_scene(t_scene *scene);

/**
 * @brief Converts a string to a double-precision floating-point number.
 *
 * Custom implementation of atof that parses:
 *     - Optional leading whitespace
 *     - Optional sign (+ or -)
 *     - Integer part (digits before decimal)
 *     - Optional decimal point and fractional part
 *     - Updates endptr to point after the parsed number
 *
 * Parsing example:
 *
 *     String: "  -42.75abc"
 *              ↑↑↑↑↑↑↑↑↑↑↑
 *              ||||||||||└─ endptr points to 'a'
 *              |||||||||└── parsed
 *              ||||||||└─── fractional part .75
 *              |||||||└──── decimal point
 *              ||||||└───── integer part 42
 *              |||||└────── sign '-'
 *              ||||└─────── whitespace skipped
 *              |||└──────── leading whitespace
 *
 * @param str The string to parse
 * @param endptr Output parameter set to point to the character after
 *               the last parsed character
 * @return double The parsed floating-point value
 *
 * @note This function does not handle scientific notation (e.g., 1.2e-3)
 * @note If no digits are found, result will be 0.0 and endptr points
 *       to the original string (after whitespace/sign)
 *
 * @see rt_parse_fraction for fractional part parsing
 */
double	rt_atof(const char *str, char **endptr);

/**
 * @brief Frees a NULL-terminated array of strings and the array itself.
 *
 * Properly deallocates memory for a token array created by rt_tokenize():
 *     1. Frees each individual string in the array
 *     2. Frees the array itself
 *     3. Handles NULL input gracefully
 *
 * Memory layout before and after:
 *
 *     Before:
 *     tokens ──► [0] ──► "sphere"
 *                [1] ──► "0,0,0"
 *                [2] ──► "10"
 *                [3] ──► "255,0,0"
 *                [4] ──► NULL
 *
 *     After:
 *     All memory freed, tokens pointer becomes dangling
 *     (caller should set to NULL after calling)
 *
 * @param split The NULL-terminated array of strings to free
 *
 * @note This function safely handles NULL input or partially allocated
 *       arrays (stops at first NULL in the array)
 * @note Does not set the input pointer to NULL - caller should do this
 *       to prevent use-after-free
 *
 * @see rt_tokenize for array creation
 */
void	rt_free_split(char **split);

/**
 * @brief Splits a string into an array of tokens based on whitespace.
 *
 * This function mimics the behavior of a simplified strtok, tokenizing
 * the input string by whitespace characters (space, tab, newline, carriage
 * return). The resulting array is NULL-terminated and must be freed with
 * rt_free_split().
 *
 * Tokenization process:
 *
 *     Input:  "  sphere  0,0,0  10  255,0,0  "
 *                ↓    ↓      ↓   ↓       ↓
 *     Tokens: ["sphere", "0,0,0", "10", "255,0,0", NULL]
 *
 * The function handles:
 *     - Leading/trailing whitespace
 *     - Multiple consecutive whitespace characters
 *     - Empty strings (returns NULL)
 *     - Memory allocation failures (frees partial tokens and returns NULL)
 *
 * @param str The input string to tokenize (not modified)
 * @return char** NULL-terminated array of token strings,
 *         or NULL if allocation fails or input is NULL
 *
 * @note The caller is responsible for freeing the returned array using
 *       rt_free_split().
 *
 * @see rt_free_split for proper deallocation
 * @see rt_count_tokens for token counting logic
 * @see rt_extract_token for individual token extraction
 */
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

/**
 * @brief Transforms a ray from world space to the 
 *        cylinder's local coordinate space.
 *
 * Creates an orthonormal basis where the cylinder's axis becomes the Y-axis,
 * simplifying intersection calculations. The transformation preserves distances
 * and angles as it uses an orthonormal basis.
 *
 * Visual representation of the transformation:
 *
 *     World Space                    Local Space (cylinder coordinates)
 *     ┌─────────────┐                 ┌─────────────┐
 *     │      ↑      │                 │      ↑      │
 *     │      │      │                 │      │      │
 *     │      │      │    ─────────►   │      │ axis │
 *     │      │      │                 │      │ (Y)  │
 *     │      │      │                 │      │      │
 *     │      │      │                 │      │      │
 *     │      │      │                 │      │      │
 *     │      │      │                 │      │      │
 *     │      │      │                 └──────┴──────┼──►
 *     └──────┴──────┼──►                  right (X)    up (Z)
 *              up (Y)  right (X)
 *
 * Mathematical process:
 * 1. Normalize cylinder orientation to get axis vector
 * 2. Build orthonormal basis (right, up) perpendicular to axis
 * 3. Project ray origin onto basis vectors using dot products
 * 4. Project ray direction onto basis vectors using dot products
 * 5. Normalize resulting local direction vector
 *
 * @param ray The ray in world space coordinates
 * @param cyl Pointer to cylinder defining the local coordinate system
 * @param local_ray Output parameter that will contain the transformed ray
 *                  in cylinder's local space where:
 *                  - Y-axis = cylinder axis
 *                  - X-axis = right vector (perpendicular to axis)
 *                  - Z-axis = up vector (completes orthonormal basis)
 *
 * @note After transformation, in local space:
 *       - The cylinder is centered at origin
 *       - The cylinder axis aligns with Y-axis
 *       - The cylinder extends from -half_height to +half_height in Y
 *       - The cylinder radius is checked in XZ plane (X² + Z² ≤ r²)
 *
 * @warning This function assumes cyl->orientation is not a zero vector.
 *          The caller should ensure orientation is valid.
 */
void	rt_transform_ray(t_ray ray, t_cylinder *cyl, t_ray *local_ray);

/**
 * @brief Solves the quadratic equation for ray-cylinder side intersection.
 *
 * In cylinder local space, the side surface is defined by x² + z² = r²,
 * independent of y (infinite cylinder). This function solves for the
 * ray parameter t where the ray satisfies this equation.
 *
 * The quadratic equation derived from substituting ray equation into cylinder:
 *
 * Given ray: (x,y,z) = (ox, oy, oz) + t*(dx, dy, dz)
 *
 * Substituting into x² + z² = r²:
 * (ox + t*dx)² + (oz + t*dz)² = r²
 *
 * Expanding:
 * (dx² + dz²)t² + 2(ox*dx + oz*dz)t + (ox² + oz² - r²) = 0
 *
 * Which matches the standard quadratic form: a·t² + b·t + c = 0
 *
 * @param local The ray in cylinder local coordinates (from rt_transform_ray)
 * @param r The cylinder radius (diameter/2)
 * @param t1 Output parameter for the first intersection distance (smaller t)
 * @param t2 Output parameter for the second intersection distance (larger t)
 * @return int 1 if solutions exist (discriminant ≥ 0), 0 otherwise
 *
 * @note The returned t values are in ray parameter space, not adjusted for
 *       cylinder height. Caller must check if corresponding y coordinates
 *       are within cylinder height using rt_within_height().
 *
 * @note If ray is parallel to cylinder axis (a ≈ 0), returns 0 as there
 *       is no side intersection (ray either misses or runs along surface).
 */
int		rt_solve_side_quadratic(t_ray local, double r, double *t1, double *t2);

/**
 * @brief Checks if a Y-coordinate in local space is 
 *        within cylinder height bounds.
 *
 * After finding intersection points on the infinite cylinder, this function
 * verifies whether the corresponding y-coordinate falls within the cylinder's
 * finite height range.
 *
 * Visual representation:
 *
 *                    ▲ Y (axis)
 *                    │
 *       half_height ─┼─── Top cap
 *                    │   ● Hit point (valid if |y| ≤ half_height)
 *                    │   │
 *                    │   │
 *                  0 ┼───┼─── Cylinder center
 *                    │   │
 *                    │   │
 *      -half_height ─┼─── Bottom cap
 *                    │
 *                    │
 *
 * @param y The Y-coordinate in local space (from ray equation: oy + t*dy)
 * @param cyl Pointer to cylinder containing half_height
 * @return int 1 if |y| ≤ half_height (within cylinder bounds + EPSILON),
 *             0 otherwise
 *
 * @note EPSILON provides a small tolerance for floating-point precision issues
 *       when the hit point is exactly at the cap boundaries.
 */
int		rt_within_height(double y, t_cylinder *cyl);

/**
 * @brief Tests intersection between a ray and the cylinder's end caps.
 *
 * Cylinders have two flat circular caps at top and bottom. This function
 * treats each cap as a plane and then checks if the plane intersection point
 * lies within the circular disk of the cap.
 *
 * Process for each cap:
 * 1. Create a plane at cap position with normal along cylinder axis
 * 2. Test ray-plane intersection
 * 3. If hit, check if hit point is within cap radius
 * 4. Keep the closest valid cap intersection
 *
 * Visual representation of cap intersection:
 *
 *                    Top cap plane
 *     ┌─────────────────────────────┐
 *     │              ▲              │
 *     │             ╱               │
 *     │            ╱ ray            │
 *     │           ╱                 │
 *     │          ╱                  │
 *     │         ● Hit point         │
 *     │       ╱  │                  │
 *     │      ╱   │                  │
 *     │     ╱    │ radius           │
 *     │    ╱     │                  │
 *     │   ╱      │                  │
 *     │  ╱       ▼                  │
 *     │ ╱     Center                │
 *     │╱                            │
 *     └─────────────────────────────┘
 *
 * @param ray The ray in world space to test against caps
 * @param cyl Pointer to cylinder containing cap geometry
 * @param hit Output parameter populated with closest cap intersection data
 * @return int 1 if any cap was hit, 0 otherwise
 *
 * @note The function checks both bottom and top caps and automatically
 *       keeps the closest intersection if multiple caps are hit.
 *
 * @warning This function assumes the ray has already been checked against
 *          the cylinder side. Caps may be hit even if side is missed.
 *
 * @see rt_set_bottom_cap, rt_set_top_cap, rt_check_cap_hit
 */
int		rt_intersect_caps(t_ray ray, t_cylinder *cyl, t_hit *hit);

/**
 * @brief Moves camera forward along its viewing direction.
 *
 * Camera moves in the direction it's pointing (orientation vector).
 * Positive speed moves forward, negative moves backward.
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_forward(t_camera *camera, double speed);

/**
 * @brief Moves camera backward (opposite of viewing direction).
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_backward(t_camera *camera, double speed);

/**
 * @brief Moves camera left (perpendicular to viewing direction).
 *
 * Uses the camera's right vector (cross product of world up and orientation)
 * to determine the left direction (negative right).
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_left(t_camera *camera, double speed);

/**
 * @brief Moves camera right (perpendicular to viewing direction).
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_right(t_camera *camera, double speed);

/**
 * @brief Moves camera up along its local up vector.
 *
 * Uses the camera's up vector (perpendicular to view direction and right)
 * to move vertically. This creates an intuitive "flying" movement where
 * up always means "toward the top of the screen" regardless of orientation.
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_up(t_camera *camera, double speed);

/**
 * @brief Moves camera down along its local up vector.
 *
 * @param camera Pointer to camera to move
 * @param speed Movement speed (units per key press)
 */
void	rt_move_camera_down(t_camera *camera, double speed);

/**
 * @brief Rotates camera orientation around its right vector (pitch).
 *
 * Pitch rotation: looking up and down.
 * Rotates around the camera's local X axis (right vector).
 *
 * @param camera Pointer to camera to rotate
 * @param angle Rotation angle in radians (positive = look up)
 */
void	rt_pitch_camera(t_camera *camera, double angle);

/**
 * @brief Rotates camera orientation around world up vector (yaw).
 *
 * Yaw rotation: looking left and right.
 * Rotates around the world Y axis (0,1,0) to maintain horizon level.
 *
 * @param camera Pointer to camera to rotate
 * @param angle Rotation angle in radians (positive = look right)
 */
void	rt_yaw_camera(t_camera *camera, double angle);

#endif
