/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/10 18:40:17 by fvoicu           ###   ########.fr       */
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
			uint32_t color = ((x * 255 / window->width) << 24) 
							| (y * 255 / window->height) << 16 
							| (x * 255 / window->width) << 8
							| 0xFF;
			mlx_put_pixel(window->img, x, y, color);
		}
	}

	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1) {
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}
