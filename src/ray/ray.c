/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/31 19:55:55 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h" 

float	calc_aspect_ratio(int width, int height)
{
	return ((float)width / (float)height);
}

void	calc_viewport_dim(t_camera *camera, float aspect_ratio, \
						float *vp_width, float *vp_height)
{
	*vp_height = 2.f * tanf(camera->fov * M_PI / 360.f);
	*vp_width = *vp_height * aspect_ratio;
}

t_ray	generate_ray(t_vec origin, t_vec direction)
{
	// t_ray	ray;

	// ray.origin = origin;
	// ray.direction = vec_unit(direction);
	// return (ray);
}


t_vec	ray_at(t_ray ray, float t)
{
	return (vec_add(ray.origin, vec_mul(ray.direction, t)));
}
