/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/18 22:48:57 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vec_scale(t_vec v, float scalar)
{
	return((t_vec){v.x * scalar, v.y * scalar, v.z * scalar});
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
	return((r << 24) | (g << 16) | (b << 8) | a);
}

t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r + (ambilight.color.r * ambilight.ratio), 255),
		.g = fmin(color.g + (ambilight.color.g * ambilight.ratio), 255),
		.b = fmin(color.b + (ambilight.color.b * ambilight.ratio), 255)
	});
}

bool	is_in_shadow(t_vec hit_point, t_light light, t_scene scene)
{
	t_vec	light_dir;
	float	light_dist;
	float	epsilon;
	t_ray	shadow_ray;
	
	epsilon = 0.001f;
	light_dir = vec_sub(light.position, hit_point);
	light_dist = vec_len(light_dir);
	light_dir = vec_unit(light_dir);
	shadow_ray = (t_ray) {
		.origin = vec_add(hit_point, vec_scale(light_dir, epsilon)),
		.direction = light_dir
	};
	float	t;
	int		i;
	
	i = -1;
	while (++i < scene.objects_nb)
	{
		if (intersect(&shadow_ray, scene.objects[i], &t) && t < light_dist )
			return (true);
	}
	return (false);
}

t_color	calc_diffuse_light(t_scene scene, t_light light, t_vec hit_point, t_vec normal)
{
	t_vec	light_dir;
	float	dot_product;

	if (is_in_shadow(hit_point, light, scene))
		return ((t_color){0, 0, 0});
	light_dir = vec_unit(vec_sub(light.position, hit_point));
	// light_dir = vec_mul(light_dir, -1);
	dot_product = fmax(vec_dot(normal, light_dir), 0.f);
	return ((t_color){
		.r = (light.color.r * dot_product * light.brightness),
		.g = (light.color.g * dot_product * light.brightness),
		.b = (light.color.b * dot_product * light.brightness)
	});
}

//TODO: calculate cylinder normal
unsigned int	get_pixel_color(int obj_idx, t_scene *scene, \
						t_ray ray, float distance)
{
	t_object	*object;
	t_color		color = {0, 0, 0};;
	t_color		ambilight;
	t_color		diffuse;
	t_color		total_color;
	t_vec		hit_point;
	t_vec		normal = {0, 0, 0};
	
	normal = (t_vec){0, 0, 0};
	object = &scene->objects[obj_idx];
	hit_point = vec_add(ray.origin, vec_mul(ray.direction, distance));
	if (obj_idx == -1)
		return (vec_to_color((	(t_color){0, 0, 0})));
	else if (object->type == SPHERE)
	{
		color = object->data.sphere.color;
		normal = vec_sub(hit_point, object->data.sphere.center);
	}
	else if (object->type == PLANE)
	{
		color = object->data.plane.color;
		normal = object->data.plane.normal;
	}
	else if (object->type == CYLINDER)
		color = object->data.cylinder.color;
	else
		color = (t_color){0, 0, 0};
	ambilight = apply_ambilight(scene->ambilight, color);
	diffuse = calc_diffuse_light(*scene, scene->light, hit_point, normal);
	total_color = (t_color){
		.r = fmin(ambilight.r + diffuse.r, 255),
		.g = fmin(ambilight.g + diffuse.g, 255),
		.b = fmin(ambilight.b + diffuse.b, 255)
	};
	return (vec_to_color(total_color)); 
}
