/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:17:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/04 04:25:05 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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