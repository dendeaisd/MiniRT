/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:22:16 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 18:56:37 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_intersections(t_ray *ray, t_scene *scene)
{
	float	closest_dist;
	int		closest_idx;
	bool	hit;
	int		i;
	float	t;

	i = -1;
	closest_dist = INFINITY;
	closest_idx = -1;
	while (++i < scene->objects_nb)
	{
		hit = false;
		if (scene->objects[i].type == SPHERE)
			hit = intersect_sphere(ray, &scene->objects[i].data.sphere, &t);
		else if (scene->objects[i].type == PLANE)
			hit = intersect_plane(ray, &scene->objects[i].data.plane, &t);
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		if (hit && t < closest_dist)
		{
			closest_idx = i;
			closest_dist = t;
		}
	}
	return (closest_idx);
}
