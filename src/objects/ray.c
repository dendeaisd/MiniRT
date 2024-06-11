/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 17:38:21 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	calc_aspect_ratio(int width, int height)
{
	return ((float)width / (float)height);
}

void	calc_viewport_dim(t_camera *camera, float aspect_ratio, \
						t_viewport *viewport)
{
	viewport->height = 2.f * tanf(camera->fov * M_PI / 360.f);
	viewport->width = viewport->height * aspect_ratio;
}

t_vec	pixel_to_viewport(int x, int y, t_viewport *viewport, \
						t_window *window)
{
	float	viewport_x;
	float	viewport_y;
	float	viewport_z;

	viewport_x = (2.f * ((x + 0.5f) / (float)window->width) - 1.f) * \
							(viewport->width / 2.f);
	viewport_y = (1.f - 2.f * ((y + 0.5) / (float)window->height)) * \
							(viewport->height / 2.f);
	viewport_z = -1.f;
	return ((t_vec){viewport_x, viewport_y, viewport_z});
}

t_vec	transform_viewport_point(t_vec viewport_point, \
						t_vec right, t_vec up, t_vec forward)
{
	t_vec	transformed_viewport_point;

	right = vec_unit(vec_cross(forward, (t_vec){0, -1, 1}));
	up = vec_cross(right, forward);
	transformed_viewport_point = vec_add(\
		vec_add(\
			vec_mul(right, viewport_point.x), \
			vec_mul(up, viewport_point.y)), \
			vec_mul(forward, viewport_point.z));
	return (transformed_viewport_point);
}

t_ray	generate_ray(t_scene *scene, t_window *window, int x, int y)
{
	t_camera	*camera;
	t_vec		viewport_point;
	t_vec		ray_direction;
	t_vec		right;
	t_vec		up;

	camera = &scene->camera;
	viewport_point = pixel_to_viewport(x, y, &camera->viewport, window);
	viewport_point = transform_viewport_point(viewport_point, right, up, \
							vec_unit(scene->camera.orientation));
	ray_direction = vec_unit(\
						vec_sub(viewport_point, camera->position));
	return ((t_ray){camera->position, ray_direction});
}
