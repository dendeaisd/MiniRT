/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 00:27:21 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/03 01:08:15 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	calculate_discriminant(t_ray *ray, t_sphere *sphere)
{
	t_vec	sphere_offset;
	float	radius;
	float	a;
	float	b;
	float	c;

	sphere_offset = vec_sub(ray->origin, sphere->center);
	radius = sphere->diameter / 2;
	a = 1; //a is normalized ==> always 1
	b = 2.f * vec_dot(sphere_offset , ray->direction);
	c = vec_dot(sphere_offset, sphere_offset) \
		- radius * radius;
	return (b * b - 4 * a * c);
}