/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 03:42:47 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "float.h"
#define NUM_SHADOW_SAMPLES 64
#define EPSILON 0.0001f

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
			hit = false;
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		else if (scene->objects[i].type == CONE)
			hit = intersect_cone(ray, &scene->objects[i].data.cone, &t);
		if (hit && t > 0.0001f && t < light_dist)
			return (true);
	}
	return (false);
}

float	rand_float(void)
{
	return (((float)rand() / RAND_MAX) * 2.0f - 1.0f);
}

t_ray	calc_shadow_ray(t_vec hit_point, \
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

t_vec uniform_grid_jitter(t_light *light, int sample, int num_samples)
{
	float jitter_amount = 8.f;
	int grid_size = (int)sqrt(num_samples);
	int x = sample % grid_size;
	int y = (sample / grid_size) % grid_size;

	float jitter_x = ((float)x / (grid_size - 1)) * jitter_amount - jitter_amount / 2.0f;
	float jitter_y = ((float)y / (grid_size - 1)) * jitter_amount - jitter_amount / 2.0f;
   	// float jitter_z = ((float)rand() / RAND_MAX) * jitter_amount - jitter_amount / 2.0f;
	float jitter_z = 0.5f;

	return vec_add(light->position, (t_vec){jitter_x, jitter_y, jitter_z});
}

// Cast object shadows with jittered light position
float cast_object_shadows(t_scene *scene, t_object *hit_object, t_vec hit_point, t_light *light)
{
	t_ray shadow_ray;
	int hits = 0;
	int i;
	float t;

	for (int j = 0; j < NUM_SHADOW_SAMPLES; ++j)
	{
		t_vec light_point = uniform_grid_jitter(light, j, NUM_SHADOW_SAMPLES);
		t_vec light_dir = vec_sub(light_point, hit_point);
		float dist_to_light = vec_len(light_dir);
		light_dir = vec_unit(light_dir);
		shadow_ray.origin = vec_add(hit_point, vec_mul(light_dir, EPSILON));
		shadow_ray.direction = light_dir;
		bool hit = false;
		i = -1;
		while (++i < scene->objects_nb)
		{
			if (scene->objects + i == hit_object)
				continue;
			t = FLT_MAX;
			hit = intersect_object(&shadow_ray, &scene->objects[i], &t);
			if (hit && t > EPSILON && t < dist_to_light)
			{
				hits++;
				break;
			}
		}
	}
	float shadow_intensity = ((float)hits / NUM_SHADOW_SAMPLES);
	return shadow_intensity;
}
