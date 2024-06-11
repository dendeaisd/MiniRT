/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviav <flaviav@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 01:42:51 by flaviav          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void render_scene(t_mini_rt *mini_rt)
{
	t_window    *window;
	t_scene		*scene;
	
	window = mini_rt->window;
	scene = mini_rt->scene;
	scene->camera.ratio = calc_aspect_ratio(window->width, window->height);
	calc_viewport_dim(&scene->camera, scene->camera.ratio, \
						&scene->camera.viewport);
	for (int y = 0; y < window->height; y++) {
		for (int x = 0; x < window->width; x++) {
			t_ray ray = generate_ray(scene, window, x, y);
			// Check for any intersection
			bool hit = false;
			for (int i = 0; i < scene->objects_nb; i++) {
				float t;
				if (intersect_sphere(&ray, &scene->objects[i].data.sphere, &t)) {
					hit = true;
					break ; // Stop checking if we find a hit
				}
			}
			uint32_t color = hit ? 0xFFFFFFFF : 0x000000FF; // White if hit, black otherwise
			mlx_put_pixel(window->img, x, y, color);
		}
	}
	
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1) {
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}
