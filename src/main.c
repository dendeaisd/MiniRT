/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 21:41:08 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	t_window window;

	window.width = 800;
	window.height = 600;

	// Init MLX
	window.mlx = mlx_init(window.width, window.height, "MLX42", true);
	if (!window.mlx) {
		fprintf(stderr, "Error initializing MLX\n");
		return EXIT_FAILURE;
	}

	// Create an image
	window.img = mlx_new_image(window.mlx, window.width, window.height);
	if (!window.img) {
		mlx_terminate(window.mlx);
		fprintf(stderr, "Error creating image\n");
		return EXIT_FAILURE;
	}
	// Draw a gradient on the image
	for (int y = 0; y < window.height; y++) {
		for (int x = 0; x < window.width; x++) {
				uint32_t color = ((x * 255 / window.width) << 24) 
								| (y * 255 / window.height) << 16 
								| (x * 255 / window.width) << 8
								| 0xFF;
				mlx_put_pixel(window.img, x, y, color);
		}
	}

	// Display the image on the window
	if (mlx_image_to_window(window.mlx, window.img, 0, 0) == -1) {
		mlx_delete_image(window.mlx, window.img);
		mlx_terminate(window.mlx);
		fprintf(stderr, "Error displaying image\n");
		return EXIT_FAILURE;
	}

	mlx_loop(window.mlx);

	mlx_terminate(window.mlx);
	return EXIT_SUCCESS;
}
