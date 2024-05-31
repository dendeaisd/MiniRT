/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:32 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/31 14:14:43 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//function pointers

static void	init_sphere(t_object *object, t_vec center, \
							float diameter, t_vec color);
static void	init_plane(t_object *object, t_vec point, \
							t_vec normal, t_vec color);
static void	init_cylinder(t_object *object, t_vec center, \
							t_vec axis, float diameter, float height, \
							t_vec color);

void	init_object(t_obj_type type, void *params)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	sphere = (t_sphere *)params;
	plane = (t_plane *)params;
	cylinder = (t_cylinder *)params;
	if (type == SPHERE)
		init_sphere(sphere, sphere->center, sphere->diameter, \
					sphere->color);
	else if (type == PLANE)
		init_plane(plane, plane->point, plane->normal, \
			plane->color);
	else if (type == CYLINDER)
		init_cylinder(cylinder, cylinder->center, cylinder->axis, \
			cylinder->diameter, cylinder->height, cylinder->color);
	else
	{
		printf("No object in the map");
		return ;
	}
}

static void	init_sphere(t_object *object, t_vec center, \
							float diameter, t_vec color)
{
	object->type = SPHERE;
	object->data.sphere.center = center;
	object->data.sphere.diameter = diameter;
	object->data.sphere.color = color;
}

static void	init_plane(t_object *object, t_vec point, \
							t_vec normal, t_vec color)
{
	object->type = PLANE;
	object->data.plane.point = point;
	object->data.plane.normal = normal;
	object->data.plane.color = color;
}

static void	init_cylinder(t_object *object, t_vec center, \
							t_vec axis, float diameter, float height, \
							t_vec color)
{
	object->type = CYLINDER;
	object->data.cylinder.center = center;
	object->data.cylinder.axis = axis;
	object->data.cylinder.diameter = diameter;
	object->data.cylinder.height = height;
	object->data.cylinder.color = color;
}
