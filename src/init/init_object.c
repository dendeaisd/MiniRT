/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 03:05:32 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/31 17:53:19 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_object(t_obj_type type, t_object *obj, void *params, \
					t_init_array *init_array)
{
	if (type < 0 || type >= \
		(sizeof(init_array->func) / sizeof(init_array->func[0])))
	{
		printf("Invalid object type\n.");
		return ;
	}
	init_array->func[type](obj, params);
}

void	init_sphere(t_object *object, void *params)
{
	t_sphere	*sphere_params;

	sphere_params = (t_sphere *)params;
	object->type = SPHERE;
	object->data.sphere.center = sphere_params->center;
	object->data.sphere.diameter = sphere_params->diameter;
	object->data.sphere.color = sphere_params->color;
}

void	init_plane(t_object *object, void *params)
{
	t_plane	*plane_params;

	plane_params = (t_plane *)params;
	object->type = PLANE;
	object->data.plane.point = plane_params->point;
	object->data.plane.normal = plane_params->normal;
	object->data.plane.color = plane_params->color;
}

void	init_cylinder(t_object *object, void *params)
{
	t_cylinder	*cylinder_params;

	cylinder_params = (t_cylinder *)params;
	object->type = CYLINDER;
	object->data.cylinder.center = cylinder_params->center;
	object->data.cylinder.axis = cylinder_params->axis;
	object->data.cylinder.diameter = cylinder_params->diameter;
	object->data.cylinder.height = cylinder_params->height;
	object->data.cylinder.color = cylinder_params->color;
}
