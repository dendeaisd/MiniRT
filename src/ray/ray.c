/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/24 01:36:18 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ray.h"

/**
 * @brief Generates a ray given an origin and a direction.
 *
 * This function initializes a ray with a given origin 
 * and direction. The direction vector is normalized, 
 * which simplifies calculations in ray tracing.
 *
 * @param origin The origin of the ray.
 * @param direction The direction of the ray.
 * @return The generated ray with normalized direction.
 */
t_ray	generate_ray(t_vec origin, t_vec direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec_unit(direction);
	return (ray);
}

/**
 * @brief Computes a point along the ray at a given distance.
 *
 * This function returns the point along the ray at 
 * distance `t` from the origin. It uses the parameter `t` 
 * to scale the direction vector and then adds it to the origin.
 *
 * @param ray The ray from which the point is computed.
 * @param t The distance along the ray to compute the point.
 * @return The computed point along the ray.
 */

t_vec	ray_at(t_ray ray, float t)
{
	return (vec_add(ray.origin, vec_mul(ray.direction, t)));
}
