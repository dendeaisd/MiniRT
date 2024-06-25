/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:27:51 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 19:54:10 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


bool	solve_quadratic_siuuu(float b, float a, float discriminant, float *t0, float *t1)
{
	float	sqrt_disc;

	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t0 = *t1 = (-b - sqrt_disc) / (2 * a);
	if (discriminant > 0)
		*t1 = (-b + sqrt_disc) / (2 * a);
	return (true);
}

void	calculate_cylinder_coefficients(t_ray *ray, t_cylinder *cylinder, float *coefficients)
{
	t_vec delta_p = vec_sub(ray->origin, cylinder->center);
	float dp_axis = vec_dot(delta_p, cylinder->axis);
	float rd_axis = vec_dot(ray->direction, cylinder->axis);
	coefficients[0] = vec_dot(ray->direction, ray->direction) - powf(rd_axis, 2); // a
	coefficients[1] = 2 * (vec_dot(ray->direction, delta_p) - rd_axis * dp_axis); // b
	coefficients[2] = vec_dot(delta_p, delta_p) - powf(dp_axis, 2) - powf(cylinder->diameter / 2, 2); // c
}

bool	check_cylinder_body_hits(t_ray *ray, t_cylinder *cylinder, float t0, float t1, float *t)
{
	// Initial checks to see if any hit is within the bounds of the cylinder
	bool hit0_valid = false, hit1_valid = false;
	float min_t = INFINITY;

	// Check the first hit point
	t_vec hit_point0 = vec_add(ray->origin, vec_mul(ray->direction, t0));
	float dist_to_cap0 = vec_dot(vec_sub(hit_point0, cylinder->center), cylinder->axis);
	if (dist_to_cap0 >= 0 && dist_to_cap0 <= cylinder->height)
	{
		hit0_valid = true;
		min_t = t0;
	}
	
	// Check the second hit point
	t_vec hit_point1 = vec_add(ray->origin, vec_mul(ray->direction, t1));
	float dist_to_cap1 = vec_dot(vec_sub(hit_point1, cylinder->center), cylinder->axis);
	if (dist_to_cap1 >= 0 && dist_to_cap1 <= cylinder->height)
	{
		hit1_valid = true;
		if (t1 < min_t) min_t = t1;
	}
	// Assign the smallest value to t
	if (hit0_valid || hit1_valid)
	{
		*t = min_t;
		return (true);
	}
	return (false);
}

bool	check_cylinder_body(t_ray *ray, t_cylinder *cylinder, float *coefficients, float *t)
{
	float a = coefficients[0];
	float b = coefficients[1];
	float discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];
	float t0, t1;
	if (discriminant < 0 || !solve_quadratic_siuuu(b, a, discriminant, &t0, &t1))
		return (false);
	return check_cylinder_body_hits(ray, cylinder, t0, t1, t);
}

bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	float coefficients[3]; //a, b, c
	t_cylinder tmp = *cylinder;
	t_plane bottom;
	t_plane top;
	bool	body_hit;
	bool	bottom_hit;
	bool 	top_hit;

	tmp.axis = vec_unit(cylinder->axis);
	make_helper_plane(&tmp, &bottom, false);
	make_helper_plane(&tmp, &top, true);
	calculate_cylinder_coefficients(ray, &tmp, coefficients);
	body_hit = check_cylinder_body(ray, &tmp, coefficients, t);
	bottom_hit = intersect_disk(ray, &bottom, t, cylinder->diameter / 2);
	top_hit = intersect_disk(ray, &top, t, cylinder->diameter / 2);
	return (body_hit || bottom_hit || top_hit);
}
