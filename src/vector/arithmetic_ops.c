/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:38:27 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/23 22:10:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec3.h"

/**
 * @brief Adds 2 vectors component-wise.
 * 
 * @param a Fist vector to add.
 * @param b Second vector to add.
 * @return	The sum of the input vectors.
*/
t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){{a.vec[X] + b.vec[X], \
					a.vec[Y] + b.vec[Y], \
					a.vec[Z] + b.vec[Z]}});
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
	return((t_vec){{a.vec[X] - b.vec[X], \
					a.vec[Y] - b.vec[Y], \
					a.vec[Z] - b.vec[Z]}});
}
