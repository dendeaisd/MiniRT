/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 12:25:43 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static unsigned int	vec_to_color(t_vec color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	
	r = (unsigned int)color.x;
	g = (unsigned int)color.y;
	b = (unsigned int)color.z;
	a = 0xFF;
	return((r << 24) | (g << 16) | (b << 8) | a);
}

unsigned int	get_pixel_color(int obj_idx, t_scene *scene)
{
	t_object	*object;
	t_vec		color;

	object = &scene->objects[obj_idx];
	if (obj_idx == -1)
		return (0x000000FF);
	else if(object->type == SPHERE)
		color = object->data.sphere.color;
	else if(object->type == PLANE)
		color = object->data.plane.color;
	else if(object->type == CYLINDER)
		color = object->data.cylinder.color;
	else
		return (0x000000FF);
	return (vec_to_color(color));
}