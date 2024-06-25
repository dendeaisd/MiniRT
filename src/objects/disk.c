/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:14:46 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 19:53:40 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "miniRT.h"

bool	check_radius(float *t, t_ray *ray, t_plane *disk, float radius)
{
	t_vec   pos;
	float		len;

	pos = vec_add(ray->origin, vec_mul(ray->direction, *t));
	len = sqrt(vec_dot(vec_sub(disk->point, pos), vec_sub(disk->point, pos)));
	if (len >= radius)
		return (false);
	return (true);
}

bool	intersect_disk(t_ray *ray, t_plane *disk, float *t, float radius)
{
	float	denominator;
	t_vec	point_to_origin;
	float	tmp;

	denominator = vec_dot(disk->normal, ray->direction);
	if (fabs(denominator) < 1e-16)
		return (false);
	point_to_origin = vec_sub(disk->point, ray->origin);
	tmp = vec_dot(point_to_origin, disk->normal) / denominator;
	if (tmp >= 0 && check_radius(&tmp, ray, disk, radius))
	{
		if (tmp < *t)
			*t = tmp;
		return (true);
	}
	return (false);
}
