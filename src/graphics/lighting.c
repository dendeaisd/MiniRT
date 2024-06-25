/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:05:20 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 13:10:01 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r * (0.1f + \
			(ambilight.color.r * ambilight.ratio / 255.0f)), 255.0f),
		.g = fmin(color.g * (0.1f + \
			(ambilight.color.g * ambilight.ratio / 255.0f)), 255.0f),
		.b = fmin(color.b * (0.1f + \
			(ambilight.color.b * ambilight.ratio / 255.0f)), 255.0f)
	});
}

static t_color	calc_diffuse_light(t_light light, t_vec hit_point, t_vec normal)
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

static t_color	calc_specular_light(t_light light, t_vec hit_point, \
						t_vec normal, t_vec view_dir)
{
	t_vec	light_dir;
	t_vec	reflect_dir;
	float	spec;

	light_dir = vec_unit(vec_sub(light.position, hit_point));
	reflect_dir = vec_sub(vec_mul(normal, 2 * \
					vec_dot(normal, light_dir)), light_dir);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), 32);
	return ((t_color){
		.r = light.color.r * spec * light.brightness,
		.g = light.color.g * spec * light.brightness,
		.b = light.color.b * spec * light.brightness});
}

t_color	calculate_lighting(t_scene *scene, \
			t_vec hit_point, t_vec normal, t_vec view_dir)
{
	t_color	diffuse_light;
	t_color	specular_light;
	t_color	total_direct_light;

	diffuse_light = calc_diffuse_light(scene->light, hit_point, normal);
	specular_light = calc_specular_light(scene->light, \
										hit_point, normal, view_dir);
	total_direct_light = (t_color){
		.r = diffuse_light.r + specular_light.r,
		.g = diffuse_light.g + specular_light.g,
		.b = diffuse_light.b + specular_light.b
	};
	return (total_direct_light);
}
