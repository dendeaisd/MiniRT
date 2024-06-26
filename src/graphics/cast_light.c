/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:03:24 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 05:18:33 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	apply_shadows(t_scene *scene, t_object *hit_object, \
					t_vec hit_point, t_vec normal)
{
	t_vec	light_dir;
	float	shadow_factor;
	t_color	direct_light;

	light_dir = vec_unit(vec_sub(scene->light.position, hit_point));
	shadow_factor = 1.0f - (cast_shadow(scene, \
					hit_point, scene->light, normal) * 0.3);
	shadow_factor *= 1.0f - cast_object_shadows(scene, \
								hit_object, hit_point, &scene->light);
	direct_light = calculate_lighting(scene, hit_point, \
				normal, vec_unit(vec_sub(scene->camera.position, hit_point)));
	return (scale_color(direct_light, shadow_factor));
}

t_color	combine_lighting(t_scene *scene, \
			t_color hit_color, t_color direct_light)
{
	t_color	ambilight;
	t_color	total_color;

	ambilight = apply_ambilight(scene->ambilight, hit_color);
	total_color = (t_color){
		.r = fmin(255, ambilight.r + direct_light.r),
		.g = fmin(255, ambilight.g + direct_light.g),
		.b = fmin(255, ambilight.b + direct_light.b)
	};
	return (gamma_correction(total_color, 1.2));
}

t_color	cast_light(t_scene *scene, \
			t_object *hit_object, t_vec hit_point)
{
	t_color	hit_color;
	t_vec	normal;
	t_vec	view_dir;
	t_color	direct_light;

	fetch_properties(hit_object, hit_point, &hit_color, &normal);
	view_dir = vec_unit(vec_sub(scene->camera.position, hit_point));
	direct_light = calculate_lighting(scene, hit_point, normal, view_dir);
	direct_light = apply_shadows(scene, \
							hit_object, hit_point, normal);
	return (clamp_color(combine_lighting(scene, hit_color, direct_light)));
}
