/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/23 05:59:24 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	pixel_to_viewport(int x, int y, t_viewport *viewport, \
						t_window *window)
{
	float	viewport_x;
	float	viewport_y;
	float	viewport_z;

	viewport_x = (2.f * ((x + 0.5f) / (float)window->width) - 1.f) * \
							(viewport->width / 2.f);
	viewport_y = -(1.f - 2.f * ((y + 0.5) / (float)window->height)) * \
							(viewport->height / 2.f);
	viewport_z = 1.f;
	return ((t_vec){viewport_x, viewport_y, viewport_z});
}

t_vec	transform_viewport_point(t_vec viewport_point, \
						t_vec right, t_vec up, t_vec forward)
{
	return (vec_add(vec_add(vec_mul(right, viewport_point.x), \
					vec_mul(up, viewport_point.y)), \
					vec_mul(forward, viewport_point.z)));
}

t_ray	generate_ray(t_scene *scene, t_window *window, int x, int y)
{
	t_camera	*camera = &scene->camera;
	t_vec		forward = vec_unit(camera->orientation);
	t_vec		global_up = {0, -1, 0};
	t_vec		right = vec_unit(vec_cross(forward, global_up));
	t_vec		up = vec_cross(right, forward);
	t_vec		viewport_point = pixel_to_viewport(x, y, &camera->viewport, window);
	viewport_point = transform_viewport_point(viewport_point, right, up, forward);
	t_vec		ray_direction = vec_unit(vec_sub(viewport_point, camera->position));
	return ((t_ray){camera->position, ray_direction});
}

