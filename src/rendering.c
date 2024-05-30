/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 22:10:29 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void render_scene(t_miniRT *miniRT)
{
    t_window    *window;
    
    window = miniRT->window;
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
