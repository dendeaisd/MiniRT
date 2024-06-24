/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 07:10:55 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	cylinder_normal(t_vec center, t_vec axis, t_vec hit_point)
{
	t_vec	closest_to_axis;
	t_vec	to_hit;
	t_vec	normal;
	t_vec	norm_axis;

	norm_axis = vec_unit(axis);
	to_hit = vec_sub(hit_point, center);
	closest_to_axis = vec_add(center, \
				vec_mul(norm_axis, \
				vec_dot(to_hit, norm_axis)));
	normal = vec_sub(hit_point, closest_to_axis);
	return (normal);
}

t_vec	cone_normal(t_vec hit_point, t_cone *cone)
{
    t_vec base_to_point = vec_sub(hit_point, cone->center);
    float height = vec_dot(base_to_point, cone->axis);
    t_vec height_component = vec_mul(cone->axis, height);
    t_vec radial_component = vec_sub(base_to_point, height_component);

    float radius = cone->diameter / 2.0f;
    float slope = radius / cone->height;

    t_vec normal = vec_add(height_component, vec_mul(radial_component, 1.0 / slope));
    return (normal);
}

t_vec	calc_normal(t_object *object, t_vec hit_point)
{
	t_vec	normal;

	normal = (t_vec){0, 0, 0};
	if (object->type == SPHERE)
		normal = vec_sub(hit_point, object->data.sphere.center);
	else if (object->type == PLANE)
		normal = object->data.plane.normal;
	else if (object->type == CYLINDER)
		normal = cylinder_normal(object->data.cylinder.center, \
							object->data.cylinder.axis, hit_point);
	else if (object->type == CONE)
		normal = cone_normal(hit_point, &object->data.cone);
	return (vec_unit(normal));
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
	else if(object->type == CONE)
		*color = object->data.cone.color;
	else
		*color = (t_color){0, 0, 0};
}

unsigned int	get_pixel_color(int obj_idx, t_scene *scene, \
						t_ray ray, float distance)
{
	t_object	*object;
	t_vec		hit_point;
	t_color		color;
	t_color		total_color;
	t_vec		normal;

	object = &scene->objects[obj_idx];
	if (obj_idx == -1)
		return (vec_to_color((t_color){0, 0, 0}));
	hit_point = vec_add(ray.origin, vec_mul(ray.direction, distance));
	color = (t_color){0, 0, 0};
	normal = (t_vec){0, 0, 0};
	fetch_properties(object, hit_point, &color, &normal);
	total_color = cast_light(scene, color, hit_point, normal);
	return (vec_to_color(total_color));
}
