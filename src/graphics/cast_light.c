/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:03:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 06:58:21 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//TODO: add clamp color func 
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

static t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r + (ambilight.color.r * ambilight.ratio), 255),
		.g = fmin(color.g + (ambilight.color.g * ambilight.ratio), 255),
		.b = fmin(color.b + (ambilight.color.b * ambilight.ratio), 255)
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

t_color scale_color(t_color color, float factor)
{
	t_color	result;

	result.r = fmin(255, color.r * factor);
	result.g = fmin(255, color.g * factor);
	result.b = fmin(255, color.b * factor);
	return (result);
}

float calculate_brightness_factor(t_scene *scene, t_vec hit_point, t_vec normal)
{
	t_vec	light_dir = vec_sub(scene->light.position, hit_point);
	float	distance = vec_len(light_dir);

	float	dot_product = vec_dot(normal, light_dir);
	dot_product = fmax(0.0, dot_product);

	float	attenuation = 1.0 / (1.f + 0.07f * distance + 0.005f * distance * distance);
	return (dot_product * attenuation);
}

t_color cast_light(t_scene *scene, t_color obj_color, t_vec hit_point, t_vec normal)
{
	t_color	ambilight = apply_ambilight(scene->ambilight, obj_color);
	t_color	diffuse_light = {0, 0, 0};
	t_color	total_color;

	if (!cast_shadow(scene, hit_point, scene->light, normal)) {
		float brightness_factor = calculate_brightness_factor(scene, hit_point, normal);
		diffuse_light = calc_diffuse_light(scene->light, hit_point, normal);
		diffuse_light = scale_color(diffuse_light, brightness_factor);
	}
	total_color = (t_color){
		.r = fmin(255, ambilight.r + diffuse_light.r),
		.g = fmin(255, ambilight.g + diffuse_light.g),
		.b = fmin(255, ambilight.b + diffuse_light.b)
	};

	return (total_color);
}
