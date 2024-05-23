/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:56:30 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/24 01:36:03 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vec3.h"

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

t_ray	generate_ray(t_vec origin, t_vec direction);
t_vec	ray_at(t_ray ray, float t);

#endif