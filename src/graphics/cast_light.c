/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviav <flaviav@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:03:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 17:10:57 by flaviav          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color clamp_color(t_color color)
{
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);
	return color;
}

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

// static t_color	apply_ambilight(t_ambilight ambilight, t_color color)
// {
// 	float	scale;

// 	scale = 0.5f;
// 	return ((t_color){
// 		.r = fmin(color.r + (ambilight.color.r * ambilight.ratio * scale), 255),
// 		.g = fmin(color.g + (ambilight.color.g * ambilight.ratio * scale), 255),
// 		.b = fmin(color.b + (ambilight.color.b * ambilight.ratio * scale), 255)
// 	});
// }
static t_color apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r * (1.0f + (ambilight.color.r / 255.0f) * ambilight.ratio), 255.0f),
		.g = fmin(color.g * (1.0f + (ambilight.color.g / 255.0f) * ambilight.ratio), 255.0f),
		.b = fmin(color.b * (1.0f + (ambilight.color.b / 255.0f) * ambilight.ratio), 255.0f)
	});
}


// static float	calc_spotlight_effect(t_vec light_dir)
// {
// 	t_vec	spotlight_dir;
// 	float	theta;
// 	float	epsilon;
// 	float	intensity;

// 	spotlight_dir = vec_unit(SPOTLIGHT_DIRECTION);
// 	theta = vec_dot(light_dir, spotlight_dir);
// 	epsilon = SPOTLIGHT_CUTOFF_ANGLE - SPOTLIGHT_OUTER_CUTOFF_ANGLE;
// 	intensity = (theta - SPOTLIGHT_OUTER_CUTOFF_ANGLE) / epsilon;
// 	intensity = fmax(fmin(intensity, 1.0), 0.0);
// 	return (intensity);
// }

// static t_color	calc_diffuse_light(t_light light, t_vec hit_point, t_vec normal)
// {
// 	t_vec	light_dir;
// 	float	dot_product;
// 	float	intensity;

// 	light_dir = vec_unit(vec_sub(light.position, hit_point));
// 	dot_product = fmax(vec_dot(normal, light_dir), 0.f);
// 	// intensity = calc_spotlight_effect(light_dir);
// 	intensity = 1.f;
// 	return ((t_color){
// 		.r = (light.color.r * dot_product * light.brightness * intensity),
// 		.g = (light.color.g * dot_product * light.brightness * intensity),
// 		.b = (light.color.b * dot_product * light.brightness * intensity)});
// }
static t_color calc_diffuse_light(t_light light, t_vec hit_point, t_vec normal)
{
	t_vec light_dir;
	float dot_product;

	light_dir = vec_unit(vec_sub(light.position, hit_point));
	dot_product = fmax(vec_dot(normal, light_dir), 0.f);
	return ((t_color){
		.r = (light.color.r * dot_product * light.brightness),
		.g = (light.color.g * dot_product * light.brightness),
		.b = (light.color.b * dot_product * light.brightness)
	});
}


static t_color	calc_specular_light(t_light light, t_vec hit_point, 
						t_vec normal, t_vec view_dir, float shininess)
{
	t_vec	light_dir;
	t_vec	reflect_dir;
	float	spec;

	light_dir = vec_unit(vec_sub(light.position, hit_point));
	reflect_dir = vec_sub(vec_mul(normal, 2 
					* vec_dot(normal, light_dir)), light_dir);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), shininess);
	return ((t_color){
		.r = light.color.r * spec * light.brightness,
		.g = light.color.g * spec * light.brightness,
		.b = light.color.b * spec * light.brightness});
}


// t_color	cast_light(t_scene *scene, t_color obj_color, 
// 						t_vec hit_point, t_vec normal, t_vec view_dir)
// {
// 	t_color	ambilight;
// 	t_color	diffuse_light;
// 	t_color	specular_light;
// 	t_color	total_color;

// 	ambilight = apply_ambilight(scene->ambilight, obj_color);
// 	diffuse_light = (t_color){0, 0, 0};
// 	specular_light = (t_color){0, 0, 0};
// 	if (!cast_shadow(scene, hit_point, scene->light, normal))
// 	{
// 		diffuse_light = calc_diffuse_light(scene->light, hit_point, normal);
// 		specular_light = calc_specular_light(scene->light, 
// 						hit_point, normal, view_dir, 32);
// 	}
// 	// 	 else
// 	// {
// 	// 	float shadow_factor = 0.5f;
// 	// 	ambilight.r = fmin(ambilight.r * shadow_factor, 255);
// 	// 	ambilight.g = fmin(ambilight.g * shadow_factor, 255);
// 	// 	ambilight.b = fmin(ambilight.b * shadow_factor, 255);

// 	// 	obj_color.r = fmin(obj_color.r * shadow_factor, 255);
// 	// 	obj_color.g = fmin(obj_color.g * shadow_factor, 255);
// 	// 	obj_color.b = fmin(obj_color.b * shadow_factor, 255);
// 	// }
// 	total_color = (t_color){
// 		.r = fmin(255, ambilight.r + diffuse_light.r + specular_light.r),
// 		.g = fmin(255, ambilight.g + diffuse_light.g + specular_light.g),
// 		.b = fmin(255, ambilight.b + diffuse_light.b + specular_light.b)};
// 	return (total_color);
// }

t_color cast_light(t_scene *scene, t_color obj_color, t_vec hit_point, t_vec normal, t_vec view_dir)
{
	t_color ambilight;
	t_color diffuse_light;
	t_color specular_light;
	t_color total_color;
	float shadow_factor = 1.0f; // No shadow by default

	ambilight = apply_ambilight(scene->ambilight, obj_color);
	diffuse_light = (t_color){0, 0, 0};
	specular_light = (t_color){0, 0, 0};

	if (!cast_shadow(scene, hit_point, scene->light, normal))
	{
		diffuse_light = calc_diffuse_light(scene->light, hit_point, normal);
		specular_light = calc_specular_light(scene->light, hit_point, normal, view_dir, 32);
	}
	else
		shadow_factor = 0.5f;
	diffuse_light.r = (int)(diffuse_light.r * shadow_factor);
	diffuse_light.g = (int)(diffuse_light.g * shadow_factor);
	diffuse_light.b = (int)(diffuse_light.b * shadow_factor);

	specular_light.r = (int)(specular_light.r * shadow_factor);
	specular_light.g = (int)(specular_light.g * shadow_factor);
	specular_light.b = (int)(specular_light.b * shadow_factor);

	total_color = (t_color){
		.r = fmin(255, ambilight.r + diffuse_light.r + specular_light.r),
		.g = fmin(255, ambilight.g + diffuse_light.g + specular_light.g),
		.b = fmin(255, ambilight.b + diffuse_light.b + specular_light.b)
	};

	return clamp_color(total_color);
}
