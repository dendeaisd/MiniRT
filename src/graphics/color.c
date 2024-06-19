/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/19 18:37:57 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//TODO: calculate cylinder normal
t_vec	calc_normal(t_object *object, t_vec hit_point)
{
	t_vec	normal;
	
	normal = (t_vec) {0, 0, 0};
	if (object->type == SPHERE)
		normal = vec_sub(hit_point, object->data.sphere.center);
	else if (object->type == PLANE)
		normal = object->data.plane.normal;
	else if (object->type == CYLINDER)
		normal = (t_vec) {0, 0, 0}; //placeholder
	return (normal);
}

void	fetch_properties(t_object *object, t_vec hit_point, \
							t_color *color, t_vec *normal)
{
	*normal = calc_normal(object, hit_point);
	if (object->type == SPHERE)
		*color = object->data.sphere.color;
	else if (object->type == PLANE)
		*color = object->data.plane.color;
	else if (object->type == CYLINDER)
		*color = object->data.cylinder.color;
	else
		*color = (t_color) {0, 0, 0};
}

unsigned int	get_pixel_color(int obj_idx, t_scene *scene, \
						t_ray ray, float distance)
{
	t_object	*object;
	t_vec 		hit_point;
	t_color		color;
	t_vec		normal;

	object = &scene->objects[obj_idx];
	if (obj_idx == -1)
		return (vec_to_color((t_color){0, 0, 0}));
	hit_point = vec_add(ray.origin, vec_mul(ray.direction, distance));
	color = (t_color){0, 0, 0};
	normal = (t_vec){0, 0, 0};
	fetch_properties(object, hit_point, &color, &normal);

	t_color		ambilight;
	t_color		diffuse;
	t_color		total_color;
	
	ambilight = apply_ambilight(scene->ambilight, color);
	diffuse = calc_diffuse_light(scene->light, hit_point, normal);
	total_color = (t_color){
		.r = fmin(ambilight.r + diffuse.r, 255),
		.g = fmin(ambilight.g + diffuse.g, 255),
		.b = fmin(ambilight.b + diffuse.b, 255)
	};
	return (vec_to_color(total_color)); 
}
