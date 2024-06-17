/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 23:08:22 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static unsigned int	vec_to_color(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	
	r = (unsigned int)color.r;
	g = (unsigned int)color.g;
	b = (unsigned int)color.b;
	a = 0xFF;
	return((r << 24) | (g << 16) | (b << 8) | a);
}

unsigned int	get_pixel_color(int obj_idx, t_scene *scene)
{
	t_object	*object;
	t_color		color;

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