/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:27:51 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/20 20:30:10 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_vec	delta_p = vec_sub(ray->origin, cylinder->center);
	float a, b, c;
	float discriminant;
	float t0, t1;
	float t_cap; 

	// Quadratic equation coefficients for cylinder intersection
	a = vec_dot(ray->direction, ray->direction) - powf(vec_dot(ray->direction, cylinder->axis), 2);
	b = 2 * (vec_dot(ray->direction, delta_p) 
			 - vec_dot(ray->direction, cylinder->axis) * vec_dot(delta_p, cylinder->axis));
	c = vec_dot(delta_p, delta_p) - powf(vec_dot(delta_p, cylinder->axis), 2) 
		- powf(cylinder->diameter / 2, 2);

	discriminant = b * b - 4 * a * c;

	// Check for parallel rays (a == 0)
	if (fabs(a) < 1e-6)
	{
		// Handle rays parallel to the cylinder axis
		if (fabs(c) > powf(cylinder->diameter / 2, 2))
			return false; // No intersection
		else
		{
			// Ray intersects both caps ==> return closest intersection
			float t_cap0 = -vec_dot(delta_p, cylinder->axis) / vec_dot(ray->direction, cylinder->axis);
			float t_cap1 = (cylinder->height - vec_dot(delta_p, cylinder->axis)) / vec_dot(ray->direction, cylinder->axis);
			*t = fmin(t_cap0, t_cap1);
			return (true);
		}
	}
	
	if (discriminant < 0) 
		return false;
	if (!solve_quadratic(b, discriminant, &t0, &t1))
		return false;

	// Check if either hit is within the cylinder's length
	t_vec hit_point0 = vec_add(ray->origin, vec_mul(ray->direction, t0));
	t_vec hit_point1 = vec_add(ray->origin, vec_mul(ray->direction, t1));

	float dist_to_cap0 = vec_dot(vec_sub(hit_point0, cylinder->center), cylinder->axis);
	float dist_to_cap1 = vec_dot(vec_sub(hit_point1, cylinder->center), cylinder->axis);

	bool hit_cylinder = false;
	if (dist_to_cap0 >= 0 && dist_to_cap0 <= cylinder->height)
	{
		*t = t0;
		hit_cylinder = true;
	}
	else if (dist_to_cap1 >= 0 && dist_to_cap1 <= cylinder->height)
	{
		*t = t1;
		hit_cylinder = true;
	}

	// Check for cap intersections ONLY if the cylinder wasn't hit
	if (!hit_cylinder)
	{
		float denom = vec_dot(ray->direction, cylinder->axis);
		if (fabs(denom) > 1e-6)  // Avoid division by zero
		{
			//top cap
			t_cap = (cylinder->height - vec_dot(delta_p, cylinder->axis)) / denom;
			if (t_cap > 0 && t_cap < *t)
			{
				t_vec hit_point = vec_add(ray->origin, vec_mul(ray->direction, t_cap));
				float dist2 = vec_dot(vec_sub(hit_point, cylinder->center), vec_sub(hit_point, cylinder->center)) - powf(cylinder->diameter / 2, 2);
				if (dist2 <= 0)
				{
					*t = t_cap;
					return true;
				}
			}

			//bottom cap
			t_cap = -vec_dot(delta_p, cylinder->axis) / denom;
			if (t_cap > 0 && t_cap < *t)
			{
				t_vec hit_point = vec_add(ray->origin, vec_mul(ray->direction, t_cap));
				float dist2 = vec_dot(vec_sub(hit_point, cylinder->center), vec_sub(hit_point, cylinder->center)) - powf(cylinder->diameter / 2, 2);
				if (dist2 <= 0)
				{
					*t = t_cap;
					return true;
				}
			}
		}
	}
	return (hit_cylinder);
}
