/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 00:27:21 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/03 01:20:22 by fvoicu           ###   ########.fr       */
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
	a = 1.f; //a is normalized ==> always 1
	b = 2.f * vec_dot(sphere_offset , ray->direction);
	c = vec_dot(sphere_offset, sphere_offset) \
		- radius * radius;
	return (b * b - 4 * a * c);
}

bool	solve_quadratic(float b, float discriminant, float *t0, float *t1)
{
	float	a;
	float	sqrt_disc;

	a = 1.f;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t0 = *t1 = (-b - sqrt_disc) / (2 * a);
	if (discriminant > 0)
		*t1 = (-b + sqrt_disc) / (2 * a);
	return (true);
}