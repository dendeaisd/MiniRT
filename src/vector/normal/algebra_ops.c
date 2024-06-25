/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:35:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/22 06:21:53 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/vec3.h"

/**
 * @brief Computes the dot product of two vectors.
 * 
 * This function takes two vectors `a` and `b`, 
 * and returns their dot product,
 * which is a scalar value representing the cosine 
 * of the angle between the two vectors
 * multiplied by their magnitudes.
 * 
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The dot product of the input vectors as a float.
 */

float	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + \
			a.y * b.y + \
			a.z * b.z);
}

/**
 * @brief Computes the cross product of two vectors.
 * 
 * This function takes two vectors `a` and `b`, and returns
 *  a vector that is perpendicular to both `a` and `b`.
 * 
 * @param a The first input vector.
 * @param b The second input vector.
 * @return A `t_vec` representing the cross product of the input vectors.
 */
t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
		a.y * b.z - a.z * b.y, \
		a.z * b.x - a.x * b.z, \
		a.x * b.y - a.y * b.x
	});
}

/**
 * @brief Normalizes a vector to a unit vector.
 * 
 * This function takes a vector `a` and
 * returns a unit vector that points 
 * in the same direction as `a`.
 * 
 * @param a The input vector to normalize.
 * @return A `t_vec` representing the unit 
 * vector of the input vector.
 */
t_vec	vec_unit(t_vec a)
{
	return (vec_div(a, sqrt(vec_dot(a, a))));
}
