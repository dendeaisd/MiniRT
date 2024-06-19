/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:47:26 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/20 01:01:16 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		// else if (scene->objects[i].type == CYLINDER)
		// 	hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		if (hit && t > 0.0001f && t < light_dist)
			return (true);
	}
	return (false);	
}

bool	cast_shadow(t_scene *scene, t_vec hit_point, t_light light, t_vec normal)
{
	t_ray	shadow_ray;
	t_vec	light_dir;
	float	light_dist;

	

	light_dir = vec_sub(light.position, hit_point);
	light_dist = vec_len(light_dir);
	shadow_ray.origin = vec_add(hit_point, vec_mul(normal, 0.01f));

	shadow_ray.direction = vec_unit(light_dir);
	return (shadow_intersect(&shadow_ray, scene, light_dist));
}
