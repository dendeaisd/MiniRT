/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:14:46 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 07:27:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void make_planes(t_cylinder *cylinder, t_plane *to_init, bool is_top)
{
  t_vec center;
  t_vec normal = vec_unit(cylinder->axis);

  center = cylinder->center;
  if (is_top == true)
	center = vec_add(cylinder->center, vec_mul(normal, cylinder->height));
  *to_init = (t_plane){
		.point = center,
		.normal = normal,
		.color = cylinder->color,
	  };
}

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

	denominator = vec_dot(disk->normal, ray->direction);
	if (fabs(denominator) < 1e-16)
		return (false);
	point_to_origin = vec_sub(disk->point, ray->origin);
	*t = vec_dot(point_to_origin, disk->normal) / denominator;
	if (*t < 0 || !check_radius(t, ray, disk, radius))
		return (false);
	return (true);
}

bool	hit_cy_caps(t_ray *ray, t_cylinder *cylinder, float *t)
{
	t_plane bottom;
	t_plane top;

	make_planes(cylinder, &bottom, false);
	make_planes(cylinder, &top, true);
	if (intersect_disk(ray, &bottom, t, cylinder->diameter / 2)
	  || intersect_disk(ray, &top, t, cylinder->diameter / 2))
	  return (true);
	return (false);
}
