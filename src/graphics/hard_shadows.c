/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_shadows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 18:37:56 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define NUM_SHADOW_SAMPLES 32
#define EPSILON 0.001f

static bool	shadow_intersect(t_ray *ray, t_scene *scene, float light_dist)
{
	float	t;
	int		i;
	bool	hit;

	i = -1;
	while (++i < scene->objects_nb)
	{
		t = INFINITY;
		hit = false;
		if (scene->objects[i].type == SPHERE)
			hit = intersect_sphere(ray, &scene->objects[i].data.sphere, &t);
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		else if (scene->objects[i].type == CONE)
			hit = intersect_cone(ray, &scene->objects[i].data.cone, &t);
		if (hit && t > 0.0001f && t < light_dist)
			return (true);
	}
	return (false);
}

static float	rand_float(void)
{
	return (((float)rand() / RAND_MAX) * 2.0f - 1.0f);
}

static t_ray	calc_shadow_ray(t_vec hit_point, \
			t_vec normal, t_vec light_dir, float filter_radius)
{
	t_ray	shadow_ray;
	t_vec	offset_dir;

	offset_dir.x = rand_float() * filter_radius;
	offset_dir.y = rand_float() * filter_radius;
	offset_dir.z = rand_float() * filter_radius;
	shadow_ray.origin = vec_add(hit_point, vec_mul(normal, EPSILON));
	shadow_ray.direction = vec_unit(vec_add(light_dir, offset_dir));
	return (shadow_ray);
}

float	cast_shadow(t_scene *scene, \
			t_vec hit_point, t_light light, t_vec normal)
{
	t_ray	shadow_ray;
	float	light_dist;
	float	shadow_intensity;
	float	filter_radius;
	int		i;

	light_dist = vec_len(vec_sub(light.position, hit_point));
	shadow_intensity = 0.f;
	if (light_dist < EPSILON)
		light_dist = EPSILON;
	filter_radius = fmin(1.f / light_dist, 1.f);
	i = -1;
	while (++i < NUM_SHADOW_SAMPLES)
	{
		shadow_ray = calc_shadow_ray(hit_point, normal, \
				vec_sub(light.position, hit_point), filter_radius);
		if (shadow_intersect(&shadow_ray, scene, light_dist))
			shadow_intensity += 1.0f;
	}
	shadow_intensity /= NUM_SHADOW_SAMPLES;
	return (shadow_intensity);
}

float	cast_object_hard_shadows(t_scene *scene, \
			t_object *hit_object, t_vec hit_point, t_vec light_dir)
{
	t_ray	shadow_ray;
	bool	hit;
	int		i;
	float	t;

	shadow_ray.origin = vec_add(hit_point, vec_mul(light_dir, EPSILON));
	shadow_ray.direction = light_dir;
	hit = false;
	i = -1;
	while (++i < scene->objects_nb)
	{
		if (scene->objects + i == hit_object)
			continue ;
		t = INFINITY;
		hit = intersect_object(&shadow_ray, &scene->objects[i], &t);
		if (hit_object->type == PLANE)
			hit = false;
		if (hit && t > EPSILON)
			return (1.f);
	}
	return (0.f);
}
