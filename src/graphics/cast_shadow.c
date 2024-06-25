/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 03:47:24 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define NUM_SHADOW_SAMPLES 32         // Number of samples per pixel
#define PCF_FILTER_WIDTH 3         // Filter width (odd number)
#define EPSILON 0.001f        

bool	shadow_intersect(t_ray *ray, t_scene *scene, float light_dist)
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
		else if (scene->objects[i].type == PLANE)
			hit = intersect_plane(ray, &scene->objects[i].data.plane, &t);
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		else if (scene->objects[i].type == CONE)
			hit = intersect_cone(ray, &scene->objects[i].data.cone, &t);
		if (hit && t > 0.0001f && t < light_dist)
			return (true);
	}
	return (false);
}

float rand_float() 
{
	return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}


bool cast_shadow(t_scene *scene, t_vec hit_point, t_light light, t_vec normal)
{
	t_ray shadow_ray;
	t_vec light_dir, offset_dir;
	float light_dist, shadow_intensity = 0.0f, filter_radius;

	light_dir = vec_sub(light.position, hit_point);
	light_dist = vec_len(light_dir);

	if (light_dist < EPSILON)
		light_dist = EPSILON;
	filter_radius = fmin(1.f / light_dist, 1.f);

	for (int i = 0; i < NUM_SHADOW_SAMPLES; ++i) 
	{
		offset_dir.x = rand_float() * filter_radius;
		offset_dir.y = rand_float() * filter_radius;
		offset_dir.z = rand_float() * filter_radius;

		shadow_ray.origin = vec_add(hit_point, vec_mul(normal, EPSILON));
		shadow_ray.direction = vec_unit(vec_add(light_dir, offset_dir));

		if (shadow_intersect(&shadow_ray, scene, light_dist))
			shadow_intensity += 1.0f;
	}
	shadow_intensity /= NUM_SHADOW_SAMPLES;
	return shadow_intensity; 
}


float cast_object_shadows(t_scene *scene, t_object *hit_object, t_vec hit_point, t_vec light_dir)
{
	t_ray	shadow_ray;
	float	t;

	shadow_ray.origin = vec_add(hit_point, vec_mul(light_dir, EPSILON)); // Bias to avoid self-shadowing
	shadow_ray.direction = light_dir;
	int i = -1;
	while (++i < scene->objects_nb)
	{
		// Exclude the hit object from shadow calculations
		if (scene->objects + i == hit_object)
			continue;

		t = INFINITY;
		bool hit = false;

		// Check for intersections with each object type
		if (scene->objects[i].type == SPHERE)
			hit = intersect_sphere(&shadow_ray, &scene->objects[i].data.sphere, &t);
		else if (scene->objects[i].type == PLANE)
			hit = intersect_plane(&shadow_ray, &scene->objects[i].data.plane, &t);
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(&shadow_ray, &scene->objects[i].data.cylinder, &t);
		else if (scene->objects[i].type == CONE)
			hit = intersect_cone(&shadow_ray, &scene->objects[i].data.cone, &t);

		if (hit && t > EPSILON) // Check for positive intersection distance
			return 1.0f;
	}
	return 0.0f;
}
