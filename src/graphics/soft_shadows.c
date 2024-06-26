/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 18:34:54 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "float.h"
#define NUM_SHADOW_SAMPLES 64
#define EPSILON 0.0001f

static t_vec uniform_grid_jitter(t_light *light, int sample, int num_samples)
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

float cast_object_soft_shadows(t_scene *scene, t_object *hit_object, t_vec hit_point, t_light *light)
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
