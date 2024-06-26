/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:17:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 05:05:54 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	make_helper_plane(t_cylinder *cylinder, t_plane *to_init, bool is_top)
{
	t_vec	center;
	t_vec	normal;

	normal = cylinder->axis;
	center = cylinder->center;
	if (is_top == true)
		center = vec_add(cylinder->center, vec_mul(normal, cylinder->height));
	*to_init = (t_plane){
		.point = center,
		.normal = normal,
		.color = cylinder->color,
	};
}

bool	intersect_plane(t_ray *ray, t_plane *plane, float *t)
{
	float	denominator;
	t_vec	point_to_origin;

	denominator = vec_dot(plane->normal, ray->direction);
	if (fabs(denominator) < 1e-16)
		return (false);
	point_to_origin = vec_sub(plane->point, ray->origin);
	*t = vec_dot(point_to_origin, plane->normal) / denominator;
	if (*t < 0)
		return (false);
	return (true);
}
