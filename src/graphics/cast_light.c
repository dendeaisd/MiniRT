/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:03:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 03:47:34 by fvoicu           ###   ########.fr       */
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

t_color scale_color(t_color color, float factor) 
{
	t_color	result;

	result.r = (unsigned char)fmin(255, color.r * factor);
	result.g = (unsigned char)fmin(255, color.g * factor);
	result.b = (unsigned char)fmin(255, color.b * factor);
	return (result);
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

static t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r * (0.1f + (ambilight.color.r * ambilight.ratio / 255.0f)), 255.0f),
		.g = fmin(color.g * (0.1f + (ambilight.color.g * ambilight.ratio / 255.0f)), 255.0f),
		.b = fmin(color.b * (0.1f + (ambilight.color.b * ambilight.ratio / 255.0f)), 255.0f)
	});
}

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

t_color	gamma_correction(t_color color, float gamma)
{
	t_color	corrected;

	corrected.r = pow(color.r / 255.0, gamma) * 255;
	corrected.g = pow(color.g / 255.0, gamma) * 255;
	corrected.b = pow(color.b / 255.0, gamma) * 255;
	return (corrected);
}

t_color cast_light(t_scene *scene, t_object *hit_object, t_vec hit_point, t_vec normal, t_vec view_dir, t_color hit_color)
{
	t_color ambilight;
	t_color diffuse_light;
	t_color specular_light;
	t_color total_color;
	float shadow_factor;
	t_vec light_dir; // Vector towards light source

	ambilight = apply_ambilight(scene->ambilight, hit_color); 
	diffuse_light = (t_color){0, 0, 0};
	specular_light = (t_color){0, 0, 0};

	// Light source shadow
	shadow_factor = 1.0f - cast_shadow(scene, hit_point, scene->light, normal); 
	light_dir = vec_unit(vec_sub(scene->light.position, hit_point)); // Direction towards light source


	// Check if in shadow of light
	if (shadow_factor > 0.0f)
	{
		diffuse_light = calc_diffuse_light(scene->light, hit_point, normal);
		specular_light = calc_specular_light(scene->light, hit_point, normal, view_dir, 32);
	}

	// Check for shadows from other objects
	shadow_factor *= (1.0f - cast_object_shadows(scene, hit_object, hit_point, light_dir)); 

	// Apply shadow factor to direct lighting (diffuse and specular)
	diffuse_light = scale_color(diffuse_light, shadow_factor);
	specular_light = scale_color(specular_light, shadow_factor);

	total_color = (t_color){
		.r = fmin(255, ambilight.r + diffuse_light.r + specular_light.r),
		.g = fmin(255, ambilight.g + diffuse_light.g + specular_light.g),
		.b = fmin(255, ambilight.b + diffuse_light.b + specular_light.b)
	};

	total_color = gamma_correction(total_color, 1.2);
	return clamp_color(total_color);
}

