/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:27:51 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/21 22:07:25 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calculate_cylinder_coefficients(t_ray *ray, t_cylinder *cylinder, float *coefficients)
{
	t_vec delta_p = vec_sub(ray->origin, cylinder->center);
	float dp_axis = vec_dot(delta_p, cylinder->axis);
	float rd_axis = vec_dot(ray->direction, cylinder->axis);
	coefficients[0] = vec_dot(ray->direction, ray->direction) - powf(rd_axis, 2); // a
	coefficients[1] = 2 * (vec_dot(ray->direction, delta_p) - rd_axis * dp_axis); // b
	coefficients[2] = vec_dot(delta_p, delta_p) - powf(dp_axis, 2) - powf(cylinder->diameter / 2, 2); // c
}

bool	check_parallel_and_caps(t_ray *ray, t_cylinder *cylinder, float *coefficients, float *t)
{
	float a = coefficients[0];
	float c = coefficients[2];
	if (fabs(a) < 1e-6)
	{
		if (fabs(c) > powf(cylinder->diameter / 2, 2))
			return (false);
		float rd_axis = vec_dot(ray->direction, cylinder->axis);
		float dp_axis = vec_dot(vec_sub(ray->origin, cylinder->center), cylinder->axis);
		float t_cap0 = -dp_axis / rd_axis;
		float t_cap1 = (cylinder->height - dp_axis) / rd_axis;
		*t = fmin(t_cap0, t_cap1);
		return true;
	}
	return (false);
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
	float b = coefficients[1];
	float discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];
	float t0, t1;
	if (discriminant < 0 || !solve_quadratic(b, discriminant, &t0, &t1))
		return (false);
	return check_cylinder_body_hits(ray, cylinder, t0, t1, t);
}

bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	float coefficients[3]; //a, b, c
	calculate_cylinder_coefficients(ray, cylinder, coefficients);
	if (check_parallel_and_caps(ray, cylinder, coefficients, t))
		return (true);
	if (check_cylinder_body(ray, cylinder, coefficients, t))
		return (true);
	return (false);
}
