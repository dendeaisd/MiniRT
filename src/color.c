/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/18 16:18:05 by fvoicu           ###   ########.fr       */
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

t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	return ((t_color){
		.r = fmin(color.r + (ambilight.color.r * ambilight.ratio), 255),
		.g = fmin(color.g + (ambilight.color.g * ambilight.ratio), 255),
		.b = fmin(color.b + (ambilight.color.b * ambilight.ratio), 255)
	});
}

unsigned int	get_pixel_color(int obj_idx, t_scene *scene)
{
	t_object	*object;
	t_color		color;
	t_color		ambilight;
	
	object = &scene->objects[obj_idx];
	if (obj_idx == -1)
		return (vec_to_color((	(t_color){0, 0, 0})));
	else if (object->type == SPHERE)
		color = object->data.sphere.color;
	else if (object->type == PLANE)
		color = object->data.plane.color;
	else if (object->type == CYLINDER)
		color = object->data.cylinder.color;
	ambilight = apply_ambilight(scene->ambilight, color);
	return (vec_to_color(ambilight)); 
}
