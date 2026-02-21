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

#endif
