/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:46:16 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 07:27:24 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool solve_quadratic_cone(float a, float b, float c, float *t0, float *t1) {
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return false;

	float sqrt_disc = sqrtf(discriminant);
	*t0 = (-b - sqrt_disc) / (2 * a);
	*t1 = (-b + sqrt_disc) / (2 * a);
	return true;
}

void calculate_cone_coefficients(t_ray *ray, t_cone *cone, float *coefficients)
{
	t_vec delta_p = vec_sub(ray->origin, cone->center);
	float radius = cone->diameter / 2.0f;
	float tan_sq = (radius / cone->height) * (radius / cone->height);
	
	coefficients[0] = vec_dot(ray->direction, ray->direction) - (1 + tan_sq) * powf(vec_dot(ray->direction, cone->axis), 2);
	coefficients[1] = 2 * (vec_dot(ray->direction, delta_p) - (1 + tan_sq) * vec_dot(ray->direction, cone->axis) * vec_dot(delta_p, cone->axis));
	coefficients[2] = vec_dot(delta_p, delta_p) - (1 + tan_sq) * powf(vec_dot(delta_p, cone->axis), 2);
}

bool check_cone_body_hits(t_ray *ray, t_cone *cone, float t0, float t1, float *t)
{
	bool hit0_valid = false, hit1_valid = false;
	float min_t = INFINITY;

	t_vec hit_point0 = vec_add(ray->origin, vec_mul(ray->direction, t0));
	float dist_to_base0 = vec_dot(vec_sub(hit_point0, cone->center), cone->axis);
	if (dist_to_base0 >= 0 && dist_to_base0 <= cone->height) {
		hit0_valid = true;
		min_t = t0;
	}

	t_vec hit_point1 = vec_add(ray->origin, vec_mul(ray->direction, t1));
	float dist_to_base1 = vec_dot(vec_sub(hit_point1, cone->center), cone->axis);
	if (dist_to_base1 >= 0 && dist_to_base1 <= cone->height) {
		hit1_valid = true;
		if (t1 < min_t) min_t = t1;
	}

	if (hit0_valid || hit1_valid) {
		*t = min_t;
		return true;
	}
	return false;
}

void make_planes_cn(t_cone *cone, t_plane *to_init, bool is_top)
{
  t_vec center;
  	t_vec normal = vec_unit(cone->axis);

	center = cone->center;
	if (is_top == true)
		center = vec_add(cone->center, vec_mul(normal, cone->height));
	*to_init = (t_plane){
		.point = center,
		.normal = normal,
		.color = cone->color,
	  };
}

bool	hit_cn_cap(t_ray *ray, t_cone *cone, float *t)
{
	t_plane bottom;

	make_planes_cn(cone, &bottom, true);
	if (intersect_disk(ray, &bottom, t, cone->diameter / 2))
	  return (true);
	return (false);
}

bool intersect_cone(t_ray *ray, t_cone *cone, float *t)
{
	t_cone tmp = *cone;
	float coefficients[3];
	tmp.axis = vec_unit(cone->axis);
	calculate_cone_coefficients(ray, &tmp, coefficients);
	float a = coefficients[0];
	float b = coefficients[1];
	float c = coefficients[2];
	float t0, t1;

	if (!solve_quadratic_cone(a, b, c, &t0, &t1))
		return(false);
	// if (hit_cn_cap(ray, &tmp, t) || check_cone_body_hits(ray, &tmp, t0, t1, t))
	// 		return true;
	if(check_cone_body_hits(ray, &tmp, t0, t1, t))
			return(true);
	return false;
}
