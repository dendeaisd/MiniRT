/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviav <flaviav@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:56 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 02:24:31 by flaviav          ###   ########.fr       */
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
	viewport_y = (1.f - 2.f* ((y + 0.5) / (float)window->height)) * \
							(viewport->height / 2.f);
	viewport_z = -1.f;
	return ((t_vec){viewport_x, viewport_y, viewport_z});
}

// t_ray	generate_ray(t_scene *scene, t_window *window, int x, int y)
// {
// 	t_camera	*camera;
// 	t_vec		viewport_point;
// 	t_vec		ray_direction;

// 	camera = &scene->camera;
// 	viewport_point = pixel_to_viewport(x, y, &camera->viewport, window);
// 	ray_direction = vec_sub(viewport_point, camera->position);
// 	// ray_direction = vec_sub(camera->position, viewport_point);	
// 	ray_direction = vec_unit(ray_direction);
// 	return ((t_ray){camera->position, ray_direction});
// }

t_ray generate_ray(t_scene *scene, t_window *window, int x, int y) {
    t_camera    *camera;
    t_vec       viewport_point;
    t_vec       ray_direction;

    camera = &scene->camera;

    viewport_point = pixel_to_viewport(x, y, &camera->viewport, window);

    // Assuming camera->orientation is the forward vector
    t_vec forward = vec_unit(camera->orientation);
    t_vec right = vec_unit(vec_cross(forward, (t_vec){0, -1, 0})); // Assuming (0, -1, 0) as world up vector
    t_vec up = vec_cross(right, forward);

    // Transform viewport point to world space using camera orientation
    t_vec transformed_viewport_point;
    transformed_viewport_point.x = viewport_point.x * right.x + viewport_point.y * up.x + viewport_point.z * forward.x;
    transformed_viewport_point.y = viewport_point.x * right.y + viewport_point.y * up.y + viewport_point.z * forward.y;
    transformed_viewport_point.z = viewport_point.x * right.z + viewport_point.y * up.z + viewport_point.z * forward.z;

    // Calculate ray direction in world space
    ray_direction = vec_sub(transformed_viewport_point, camera->position);
    ray_direction = vec_unit(ray_direction); // Normalize direction
    return (t_ray){camera->position, ray_direction};
}
