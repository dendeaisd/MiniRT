/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:40:21 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/27 03:43:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define STAR_SPAWN_RANGE 10.0f
#define MAX_ANGLE 0.01

unsigned int	get_star_color(void)
{
	const unsigned int	star_colors[] = {0xFFFFFF, 0xFFFF00, \
							0x00FFFF, 0x0000FF};
	int					num_colors;
	int					random_index;

	num_colors = sizeof(star_colors) / sizeof(star_colors[0]);
	random_index = rand() % num_colors;
	return (star_colors[random_index]);
}

bool	is_star_hit(t_ray ray)
{
	t_vec	star_pos;
	float	dot_product;
	float	angle;

	star_pos.x = (float)rand() / RAND_MAX * STAR_SPAWN_RANGE \
										- STAR_SPAWN_RANGE / 2.0f;
	star_pos.y = (float)rand() / RAND_MAX * STAR_SPAWN_RANGE \
										- STAR_SPAWN_RANGE / 2.0f;
	star_pos.z = (float)rand() / RAND_MAX * STAR_SPAWN_RANGE \
										- STAR_SPAWN_RANGE / 2.0f;
	dot_product = vec_dot(ray.direction, star_pos);
	angle = acosf(dot_product / (vec_len(ray.direction) * vec_len(star_pos)));
	return (angle < MAX_ANGLE);
}
