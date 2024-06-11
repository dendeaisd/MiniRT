/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 19:15:03 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void	setup_camera(t_camera *camera, int width, int height)
{
	camera->ratio = calc_aspect_ratio(width, height);
	calc_viewport_dim(camera, camera->ratio, \
						&camera->viewport);
}

bool	check_intersections(t_ray *ray, t_scene *scene)
{
	int	i;
	float t;

	i = -1;
	while (++i < scene->objects_nb)
	{
		if (intersect_sphere(ray, &scene->objects[i].data.sphere, &t))
			return (true);
	}
	return (false);
}

unsigned int	get_pixel_color(bool hit)
{
	if ( hit = true)
		return (0xFFFFFFFF);
	return (0x000000FF);
}

void	display_img(t_window *window)
{
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}

void	render_scene(t_mini_rt *mini_rt)
{
	t_window	*window;
	t_scene		*scene;

	window = mini_rt->window;
	scene = mini_rt->scene;
}






// void render_scene(t_mini_rt *mini_rt)
// {
// 	t_window    *window;
// 	t_scene		*scene;
	
// 	window = mini_rt->window;
// 	scene = mini_rt->scene;

// 	scene->camera.ratio = calc_aspect_ratio(window->width, window->height);
// 	calc_viewport_dim(&scene->camera, scene->camera.ratio, \
// 						&scene->camera.viewport);
// 	for (int y = 0; y < window->height; y++) {
// 		for (int x = 0; x < window->width; x++) {
// 			t_ray ray = generate_ray(scene, window, x, y);
// 			// Check for any intersection
// 			bool hit = false;
// 			for (int i = 0; i < scene->objects_nb; i++) {
// 				float t;
// 				if (intersect_sphere(&ray, &scene->objects[i].data.sphere, &t)) {
// 					hit = true;
// 					break ; // Stop checking if we find a hit
// 				}
// 			}
// 			uint32_t color = hit ? 0xFFFFFFFF : 0x000000FF; // White if hit, black otherwise
// 			mlx_put_pixel(window->img, x, y, color);
// 		}
// 	}
	
// 	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1) {
// 		mlx_delete_image(window->mlx, window->img);
// 		mlx_terminate(window->mlx);
// 		fprintf(stderr, "Error displaying image\n");
// 	}
// }
