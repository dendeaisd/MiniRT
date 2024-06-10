/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 00:27:21 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/10 19:09:14 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	calculate_discriminant(t_ray *ray, t_sphere *sphere, \
							float *b, float *c)
{
	t_vec	sphere_offset;
	float	radius;
	float	a;

	sphere_offset = vec_sub(ray->origin, sphere->center);
	radius = sphere->diameter / 2;
	a = 1.f; //a is normalized ==> always 1
	*b = 2.f * vec_dot(sphere_offset , ray->direction);
	*c = vec_dot(sphere_offset, sphere_offset) \
		- radius * radius;
	return (*b * *b - 4 * a * *c);
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

bool	find_closest_hit(float t0, float t1, float *t)
{
	if (t0 > 0 && t1 > 0)
	{
		if (t0 < t1)
			*t = t0;
		else 
			*t = t1;
		return (true);
	}
	else if(t0 > 0)
		return (*t = t0, true);
	else if (t1 > 0)
		return (*t = t1, true);
	return (false);
}

bool	intersect_sphere(t_ray *ray, t_sphere *sphere, float *t)
{
	float	discriminant;
	float	b;
	float	c;
	float	t0;
	float	t1;

	discriminant = calculate_discriminant(ray, sphere, &b, &c);
	if (!solve_quadratic(b, discriminant, &t0, &t1))
		return (false);
	if (find_closest_hit(t0, t1, t))
		return (true);
	return (false);
}