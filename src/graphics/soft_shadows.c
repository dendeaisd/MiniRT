/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/27 00:52:55 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "float.h"
#define NUM_SHADOW_SAMPLES 64
#define EPSILON 0.0001f

static t_vec	uniform_grid_jitter(t_light *light, int sample, int num_samples)
{
	const float	jitter_amount = 8.f;
	int			grid_size;
	int			x;
	int			y;
	float		jitter[3];

	grid_size = (int)sqrt(num_samples);
	x = sample % grid_size;
	y = (sample / grid_size) % grid_size;
	jitter[0] = ((float)x / (grid_size - 1)) * jitter_amount - \
			jitter_amount / 2.0f;
	jitter[1] = ((float)y / (grid_size - 1)) * jitter_amount - \
			jitter_amount / 2.0f;
	jitter[2] = 0.5f;
	return (vec_add(light->position, (t_vec){jitter[0], jitter[1], jitter[2]}));
}

static void	init_soft_shadow_data(t_soft_shadow_data *data, t_light *light, \
		int j, t_vec hit_point)
{
	data->light_point = uniform_grid_jitter(light, j, NUM_SHADOW_SAMPLES);
	data->light_dir = vec_sub(data->light_point, hit_point);
	data->to_light = vec_len(data->light_dir);
	data->light_dir = vec_unit(data->light_dir);
	data->ray.origin = vec_add(hit_point, \
								vec_mul(data->light_dir, EPSILON));
	data->ray.direction = data->light_dir;
	data->hit = false;
}

float	cast_object_soft_shadows(t_scene *scene, t_object *hit_object, \
		t_vec hit_point, t_light *light)
{
	t_soft_shadow_data	data;
	int					i;
	int					j;
	float				t;
	float				shadow_intensity;

	data.hits = 0;
	j = -1;
	while (++j < NUM_SHADOW_SAMPLES)
	{
		init_soft_shadow_data(&data, light, j, hit_point);
		i = -1;
		while (++i < scene->objects_nb)
		{
			if (scene->objects + i == hit_object)
				continue ;
			t = FLT_MAX;
			data.hit = intersect_object(&data.ray, &scene->objects[i], &t);
			if (data.hit && t > EPSILON && t < data.to_light && ++data.hits)
				break ;
		}
	}
	shadow_intensity = ((float)data.hits / NUM_SHADOW_SAMPLES);
	return (shadow_intensity);
}
