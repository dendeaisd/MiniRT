/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:01:15 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 13:12:44 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	clamp_color(t_color color)
{
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);
	return (color);
}

t_color	scale_color(t_color color, float factor)
{
	t_color	result;

	result.r = (unsigned char)fmin(255, color.r * factor);
	result.g = (unsigned char)fmin(255, color.g * factor);
	result.b = (unsigned char)fmin(255, color.b * factor);
	return (result);
}

unsigned int	vec_to_color(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = (unsigned int)color.r;
	g = (unsigned int)color.g;
	b = (unsigned int)color.b;
	a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

t_color	gamma_correction(t_color color, float gamma)
{
	t_color	corrected;

	corrected.r = pow(color.r / 255.0, gamma) * 255;
	corrected.g = pow(color.g / 255.0, gamma) * 255;
	corrected.b = pow(color.b / 255.0, gamma) * 255;
	return (corrected);
}

/**
 * TODO: Definitely doesn t belong here....
 **/
bool	intersect_object(t_ray *ray, t_object *object, float *t)
{
	if (object->type == SPHERE)
		return (intersect_sphere(ray, &object->data.sphere, t));
	else if (object->type == PLANE)
		return (intersect_plane(ray, &object->data.plane, t));
	else if (object->type == CYLINDER)
		return (intersect_cylinder(ray, &object->data.cylinder, t));
	else if (object->type == CONE)
		return (intersect_cone(ray, &object->data.cone, t));
	return (false);
}
