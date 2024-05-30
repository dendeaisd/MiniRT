/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 22:14:35 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	t_miniRT *miniRT = malloc(sizeof(miniRT));
	miniRT->window = malloc(sizeof(t_window));
	
	t_window *window;
	window = miniRT->window;
	window->width = 800;
	window->height = 600;
	// Init MLX
	window->mlx = mlx_init(window->width, window->height, "MLX42", true);
	if (!window->mlx) {
		fprintf(stderr, "Error initializing MLX\n");
		return EXIT_FAILURE;
	}

	// Create an image
	window->img = mlx_new_image(window->mlx, window->width, window->height);
	if (!window->img) {
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error creating image\n");
		return EXIT_FAILURE;
	}
	render_scene(miniRT);

	mlx_loop(window->mlx);

	mlx_terminate(window->mlx);
	return EXIT_SUCCESS;
}
