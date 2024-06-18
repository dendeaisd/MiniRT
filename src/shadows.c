/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:46:32 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/18 20:09:18 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	sample_sphere_surface(t_light light)
{
	float	u, v, theta, phi, x, y, z;
	t_vec	sample_point;

	u = (float)rand() / RAND_MAX;
	v = (float)rand() / RAND_MAX;
	theta = 2 * M_PI * u;
	phi = acos(2 * v - 1);
	x = sin(phi) * cos(theta);
	y = sin(phi) * sin(theta);
	z = cos(phi);

	sample_point = (t_vec){
		.x = light.position.x + x * LIGHT_RADIUS,
		.y = light.position.y + y * LIGHT_RADIUS,
		.z = light.position.z + z * LIGHT_RADIUS
	};
	return(sample_point);
}

float	calc_soft_shadow(t_vec hit_point, t_scene scene, \
				t_light light, int sample_nb)
{
	t_ray	shadow_ray;
	t_vec	light_pos;
	t_vec	to_light;
	int		shadow_num;
	int		i;
	
	shadow_num = 0;
	i = -1;
	while (++i < sample_nb)
	{
		light_pos = sample_sphere_surface(light);
		to_light = vec_unit(vec_sub(light_pos, hit_point));
		shadow_ray = (t_ray){hit_point, to_light};
		if (is_occluded(shadow_ray, scene))
			shadow_num++;
	}
	return (1.f - ((float)shadow_num / (float)sample_nb));
}