/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:35:02 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 05:23:46 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>
# include <immintrin.h> 

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, float scalar);
t_vec	vec_div(t_vec a, float scalar);
float	vec_len(t_vec v);
float	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_unit(t_vec a);

#endif