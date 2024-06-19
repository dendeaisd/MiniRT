/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:03:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/19 18:06:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	vec_to_color(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = (unsigned int)color.r;
	g = (unsigned int)color.g;
	b = (unsigned int)color.b;
	a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r + (ambilight.color.r * ambilight.ratio), 255),
		.g = fmin(color.g + (ambilight.color.g * ambilight.ratio), 255),
		.b = fmin(color.b + (ambilight.color.b * ambilight.ratio), 255)
	});
}

t_color	calc_diffuse_light(t_light light, t_vec hit_point, t_vec normal)
{
	t_vec	light_dir;
	float	dot_product;

	light_dir = vec_unit(vec_sub(light.position, hit_point));
	dot_product = fmax(vec_dot(normal, light_dir), 0.f);
	return ((t_color){
		.r = (light.color.r * dot_product * light.brightness),
		.g = (light.color.g * dot_product * light.brightness),
		.b = (light.color.b * dot_product * light.brightness)
	});
}
