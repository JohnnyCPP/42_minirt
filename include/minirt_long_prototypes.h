/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_long_prototypes.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#             */
/*   Updated: 2025/12/17 02:49:28 by jonnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_LONG_PROTOTYPES_H
# define MINIRT_LONG_PROTOTYPES_H

/**
 * @brief Adds two vectors component-wise.
 *
 * result.x = v1.x + v2.x
 * result.y = v1.y + v2.y
 * result.z = v1.z + v2.z
 *
 * @param v1 First vector
 * @param v2 Second vector
 * @return t_coordinates Component-wise sum of v1 and v2
 */
t_coordinates	rt_add_vector(t_coordinates v1, t_coordinates v2);

/**
 * @brief Subtracts vector v2 from v1 component-wise.
 *
 * result.x = v1.x - v2.x
 * result.y = v1.y - v2.y
 * result.z = v1.z - v2.z
 *
 * @param v1 Vector to subtract from
 * @param v2 Vector to subtract
 * @return t_coordinates Component-wise difference v1 - v2
 */
t_coordinates	rt_subtract_vector(t_coordinates v1, t_coordinates v2);

/**
 * @brief Multiplies a vector by a scalar value.
 *
 * result.x = v.x * scalar
 * result.y = v.y * scalar
 * result.z = v.z * scalar
 * Used for scaling vectors or moving along a direction.
 *
 * @param v Input vector
 * @param scalar Scalar multiplier
 * @return t_coordinates Scaled vector
 */
t_coordinates	rt_multiply_vector(t_coordinates v, double scalar);

/**
 * @brief Normalizes a vector to unit length (magnitude = 1).
 *
 * If the vector magnitude is near zero (< 1e-6), returns the original
 * vector to avoid division by zero. Useful for creating direction vectors.
 *
 * @param v Vector to normalize
 * @return t_coordinates Unit vector pointing in same direction as v
 */
t_coordinates	rt_normalize_vector(t_coordinates v);

/**
 * @brief Negates a vector (multiplies by -1).
 *
 * result.x = -v.x
 * result.y = -v.y
 * result.z = -v.z
 * Used to reverse direction or get opposite normal.
 *
 * @param v Vector to negate
 * @return t_coordinates Negated vector
 */
t_coordinates	rt_negate_vector(t_coordinates v);

/**
 * @brief Computes the point at distance t along a ray: O + t*D.
 *
 * For t > 0: point in front of ray origin
 * For t = 0: ray origin
 * For t < 0: point behind ray origin (shouldn't be visible)
 *
 * @param ray Ray to evaluate
 * @param t Distance parameter along the ray
 * @return t_coordinates Point at distance t from origin in ray direction
 */
t_coordinates	rt_get_point(t_ray ray, double t);

/**
 * @brief Converts pixel coordinates to a point on the viewport.
 *
 * Parameters x and y are ratios whose values are in range [-1, 1] where:
 * - (-1, -1) is bottom-left corner
 * - (1, 1) is top-right corner
 *
 * The viewport is placed at distance 1 from camera for simplicity,
 * then scaled by tan(FOV/2) to account for field of view.
 */
t_coordinates	rt_get_viewport_point(t_camera *camera, double x, double y);

/**
 * @brief Calculates the camera's right vector (X axis) from its orientation.
 *
 * Uses the cross product between the world up vector (0,1,0) and the camera's
 * forward orientation vector to compute a perpendicular vector pointing to
 * the camera's right side. The result is normalized to unit length.
 *
 * The right vector forms the camera's local X axis and is used together with
 * the up vector to create an orthonormal basis for camera space.
 *
 * Example: If camera is looking along +Z (0,0,1), the right vector is (1,0,0)
 *
 * Think of a Basis as a coordinate system: A set of reference directions 
 * that tell you how to measure positions in space.
 * "orthonormal" combines two concepts:
 * - Orthogonal (perpendicular): All axes are at 90° angles to each other
 * - Normal (unit length): Each axis vector has length 1
 *
 * @param camera Pointer to camera structure containing orientation
 * @return t_coordinates Normalized right vector (camera's local X axis)
 */
t_coordinates	rt_get_camera_right(t_camera *camera);

/**
 * @brief Calculates the camera's up vector (Y axis) from its orientation.
 *
 * Computes the up vector by taking the cross product of the camera's forward
 * orientation vector with its right vector. This ensures a consistent
 * orthonormal basis where the up vector is perpendicular to both forward
 * and right directions. The result is normalized to unit length.
 *
 * The up vector forms the camera's local Y axis and defines which direction
 * is "up" for the camera. This is used when mapping screen coordinates to
 * viewport points.
 *
 * Example: If camera is looking along +Z (0,0,1) and right is (1,0,0),
 *          the up vector is (0,1,0)
 *
 * @param camera Pointer to camera structure containing orientation
 * @return t_coordinates Normalized up vector (camera's local Y axis)
 */
t_coordinates	rt_get_camera_up(t_camera *camera);

/**
 * @brief Computes the surface normal vector at a point on the cylinder's side.
 *
 * The normal at any point on a cylinder's side is 
 * perpendicular to the cylinder's axis and 
 * points radially outward from the axis to the surface point.
 *
 * Mathematical derivation:
 * 1. Let axis = normalized cylinder orientation vector
 * 2. Let to_point = vector from cylinder center to hit point
 * 3. The projection of to_point onto the axis is: (to_point · axis) * axis
 * 4. The radial component (perpendicular to axis) is: to_point - projection
 * 5. This radial component is exactly the normal direction (outward from axis)
 *
 * Visual representation:
 *
 *                    Normal (radially outward)
 *                         ↑
 *                         |
 *                         |   ● Hit point
 *                         |  /
 *                         | /
 *      Axis ──────────────┼/────────────►
 *                        /│
 *                       / |
 *                      /  |
 *                     ●   |
 *                 Center  |
 *                         ↓
 *                    Projected point
 *                    on axis
 *
 * The normal is normalized to unit length before return.
 *
 * @param point The hit point on the cylinder surface (world coordinates)
 * @param cyl Pointer to cylinder structure containing:
 *            - center: Center point of cylinder
 *            - orientation: Direction vector of cylinder axis
 *            - radius: Cylinder radius (precomputed)
 * @return t_coordinates Unit normal vector pointing outward from cylinder axis
 *
 * @note The returned normal is guaranteed to be perpendicular to the cylinder
 *       axis (dot product with axis ≈ 0) and have unit length.
 *
 * @warning This function assumes point actually lies on the cylinder surface.
 *          If point is inside the cylinder, the result will still point
 *          radially outward but may not be accurate for lighting calculations.
 */
t_coordinates	rt_get_side_normal(t_coordinates point, t_cylinder *cyl);

/**
 * @brief Computes the cross product of two vectors.
 *
 * The cross product v1 × v2 produces a vector perpendicular to both inputs,
 * with magnitude equal to the area of the parallelogram they span.
 * Direction follows the right-hand rule.
 *
 * Mathematical formula:
 *     result.x = v1.y * v2.z - v1.z * v2.y
 *     result.y = v1.z * v2.x - v1.x * v2.z
 *     result.z = v1.x * v2.y - v1.y * v2.x
 *
 * @param v1 First vector
 * @param v2 Second vector
 * @return t_coordinates Cross product v1 × v2
 */
t_coordinates	rt_crossprod_of(t_coordinates v1, t_coordinates v2);

#endif
