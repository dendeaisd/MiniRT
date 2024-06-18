/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:24:43 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/18 15:44:47 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static unsigned int	vec_to_color(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = 0xFF;
	return((r << 24) | (g << 16) | (b << 8) | a);
}

// unsigned int	get_pixel_color(int obj_idx, t_scene *scene)
// {
// 	t_object	*object;
// 	t_color		color;

// 	object = &scene->objects[obj_idx];
// 	if (obj_idx == -1)
// 		return (0x000000FF);
// 	else if(object->type == SPHERE)
// 		color = object->data.sphere.color;
// 	else if(object->type == PLANE)
// 		color = object->data.plane.color;
// 	else if(object->type == CYLINDER)
// 		color = object->data.cylinder.color;
// 	else
// 		return (0x000000FF);
// 	return (vec_to_color(color));
// }

t_color	apply_ambilight(t_ambilight ambilight, t_color color)
{
	t_color	norm_ambilight;

	norm_ambilight = (t_color){
		.r = ambilight.color.r / 255,
		.g = ambilight.color.g / 255,
		.b = ambilight.color.b / 255,
	};
	// return ((t_color){
	// 	.r = color.r * (ambilight.color.r * ambilight.ratio),
	// 	.g = color.g * (ambilight.color.g * ambilight.ratio),
	// 	.b = color.b * (ambilight.color.b * ambilight.ratio),
	// });
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
	t_color		norm_color;
	t_color		background;

	background = (t_color){1, 1, 1};
	object = &scene->objects[obj_idx];
	if (obj_idx == -1)
	{
		ambilight = apply_ambilight(scene->ambilight, background);
		return (vec_to_color(ambilight));
	}
	else if (object->type == SPHERE)
		color = object->data.sphere.color;
	else if (object->type == PLANE)
		color = object->data.plane.color;
	else if (object->type == CYLINDER)
		color = object->data.cylinder.color;
	// norm_color = (t_color) {
	// 	.r = color.r / 255,
	// 	.g = color.g / 255,
	// 	.b = color.b / 255,
	// };
	ambilight = apply_ambilight(scene->ambilight, color);
	return (vec_to_color(ambilight));
}
