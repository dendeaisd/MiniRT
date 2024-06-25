/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:38:27 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 06:00:47 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/vec3.h"

/**
 * @brief Adds 2 vectors component-wise.
 * 
 * @param a Fist vector to add.
 * @param b Second vector to add.
 * @return	The sum of the input vectors.
*/
t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, \
					a.y + b.y, \
					a.z + b.z});
}

/**
 * @brief Substracts 2 vectors component-wise.
 * 
 * @param a The vector form which to substract.
 * @param b The vector to substract from 'a'.
 * @return	The difference of the input vectors.
*/
t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, \
					a.y - b.y, \
					a.z - b.z});
}

/**
 * @brief Multiplies a vector by a scalar.
 * 
 * @param a The vector to be multiplied.
 * @param scalar The scalar value to multiply with.
 * @return A vector representing the result of the
 * scalar multiplication.
*/
t_vec	vec_mul(t_vec a, float scalar)
{
	return ((t_vec){a.x * scalar, \
					a.y * scalar, \
					a.z * scalar});
}

/**
 * @brief Divides a vector by a scalar.
 * 
 * @param a The vector to be divided.
 * @param scalar The scalar value to divide by.
 * @return A vector representing the result of the
 * scalar division.
*/
t_vec	vec_div(t_vec a, float scalar)
{
	return ((t_vec){a.x / scalar, \
					a.y / scalar, \
					a.z / scalar});
}

float	vec_len(t_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
