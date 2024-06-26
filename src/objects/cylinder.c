/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:27:51 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 05:17:56 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	solve_quadratic_siuuu(float *coefficients, float *t0, float *t1)
{
	float	discriminant;
	float	sqrt_disc;
	float	a;
	float	b;
	float	c;

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

static void	calculate_coefficients(t_ray *ray, t_cylinder *cy, float *coeffs)
{
	t_vec	delta_p;
	float	dp_axis;
	float	rd_axis;
	float	radius;

	radius = cy->diameter / 2;
	delta_p = vec_sub(ray->origin, cy->center);
	dp_axis = vec_dot(delta_p, cy->axis);
	rd_axis = vec_dot(ray->direction, cy->axis);
	coeffs[0] = vec_dot(ray->direction, ray->direction) - powf(rd_axis, 2);
	coeffs[1] = 2 * (vec_dot(ray->direction, delta_p) - rd_axis * dp_axis);
	coeffs[2] = vec_dot(delta_p, delta_p) - powf(dp_axis, 2) - powf(radius, 2);
}

static bool	calc_hit(t_ray *ray, t_cylinder *cy, float dist, float *t)
{
	t_vec	hit_point;
	float	dist_to_cap;

	hit_point = vec_add(ray->origin, vec_mul(ray->direction, dist));
	dist_to_cap = vec_dot(vec_sub(hit_point, cy->center), cy->axis);
	if (dist_to_cap >= 0 && dist_to_cap <= cy->height)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	check_cy_body(t_ray *ray, t_cylinder *cy, float *coeffs, float *t)
{
	float	t0;
	float	t1;
	float	tmp;
	bool	hit0_valid;
	bool	hit1_valid;

	tmp = INFINITY;
	hit0_valid = false;
	hit1_valid = false;
	if (!solve_quadratic_siuuu(coeffs, &t0, &t1))
		return (false);
	hit0_valid = calc_hit(ray, cy, t0, &tmp);
	hit1_valid = calc_hit(ray, cy, t1, &tmp);
	if (hit0_valid || hit1_valid)
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	float		coefficients[3];
	t_cylinder	tmp;
	t_plane		bottom;
	t_plane		top;
	bool		hits[3];

	tmp = *cylinder;
	tmp.axis = vec_unit(cylinder->axis);
	make_helper_plane(&tmp, &bottom, false);
	make_helper_plane(&tmp, &top, true);
	calculate_coefficients(ray, &tmp, coefficients);
	hits[0] = check_cy_body(ray, &tmp, coefficients, t);
	hits[1] = intersect_disk(ray, &bottom, t, cylinder->diameter / 2);
	hits[2] = intersect_disk(ray, &top, t, cylinder->diameter / 2);
	return (hits[0] || hits[1] || hits[2]);
}
