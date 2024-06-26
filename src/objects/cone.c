/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:46:16 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 05:05:06 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	solve_quadratic_cone(float *coefficients, float *t0, float *t1)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_disc;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t0 = (-b - sqrt_disc) / (2 * a);
	*t1 = (-b + sqrt_disc) / (2 * a);
	return (true);
}

static void	calculate_coefficients(t_ray *ray, t_cone *cone, float *coeffs)
{
	t_vec	delta_p;
	float	radius;
	float	tsq;
	float	ray_cn;
	float	p_cn;

	delta_p = vec_sub(ray->origin, cone->center);
	radius = cone->diameter / 2.0f;
	tsq = 1 + ((radius / cone->height) * (radius / cone->height));
	ray_cn = vec_dot(ray->direction, cone->axis);
	p_cn = vec_dot(delta_p, cone->axis);
	coeffs[0] = vec_dot(ray->direction, ray->direction) - tsq * powf(ray_cn, 2);
	coeffs[1] = 2 * (vec_dot(ray->direction, delta_p) - tsq * ray_cn * p_cn);
	coeffs[2] = vec_dot(delta_p, delta_p) - tsq * powf(p_cn, 2);
}

static bool	calc_hit(t_ray *ray, t_cone *cone, float dist, float *t)
{
	t_vec	hit_point;
	float	dist_to_base;

	hit_point = vec_add(ray->origin, vec_mul(ray->direction, dist));
	dist_to_base = vec_dot(vec_sub(hit_point, cone->center), cone->axis);
	if (dist_to_base >= 0 && dist_to_base <= cone->height)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	check_cone_body(t_ray *ray, t_cone *cone, float *coeffs, float *t)
{
	bool	hit0_valid;
	bool	hit1_valid;
	float	tmp;
	float	t0;
	float	t1;

	tmp = INFINITY;
	if (!solve_quadratic_cone(coeffs, &t0, &t1))
		return (false);
	hit0_valid = calc_hit(ray, cone, t0, &tmp);
	hit1_valid = calc_hit(ray, cone, t1, &tmp);
	if (hit0_valid || hit1_valid)
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

bool	intersect_cone(t_ray *ray, t_cone *cone, float *t)
{
	t_cone	tmp;
	float	coefficients[3];
	t_plane	bottom;
	bool	hit_body;
	bool	hit_cap;

	tmp = *cone;
	tmp.axis = vec_unit(cone->axis);
	make_helper_plane((t_cylinder *)(&tmp), &bottom, true);
	calculate_coefficients(ray, &tmp, coefficients);
	hit_body = check_cone_body(ray, &tmp, coefficients, t);
	hit_cap = intersect_disk(ray, &bottom, t, cone->diameter / 2);
	return (hit_body || hit_cap);
}
