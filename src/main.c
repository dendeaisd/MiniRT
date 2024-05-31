/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/01 01:02:42 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void print_obj_data(t_object *obj)
// {
// 	switch (obj->type)
// 	{
// 		case SPHERE:
// 			printf("Diameter: %f",obj->data.sphere.diameter);
// 			break;
// 		default:
// 			printf("Object was not initialized.\n");
// 	}
// }

// int	main(void)
// {
// 	t_mini_rt	*mini_rt;

// 	mini_rt = init_mini_rt(WIDTH, HEIGHT);
// 	if (!mini_rt)
// 		return (fprintf(stderr, "Failed to init miniRT\n"), \
// 				EXIT_FAILURE);
// 	render_scene(mini_rt);
// 	mlx_loop(mini_rt->window->mlx);
// 	print_obj_data(mini_rt->scene->objects);
// 	destroy_mini_rt(mini_rt);
// 	return (EXIT_SUCCESS);
// }

//Testing the ray funcs:
int main() {
	// Test calc_aspect_ratio
	int width = 1920;
	int height = 1080;
	float aspect_ratio = calc_aspect_ratio(width, height);
	printf("Aspect Ratio (1920x1080): %f\n", aspect_ratio);

	// Setup for testing calc_viewport_dim
	t_camera camera = {.fov = 90.0};
	t_viewport viewport;
	calc_viewport_dim(&camera, aspect_ratio, &viewport);
	printf("Viewport dimensions: width = %f, height = %f\n", viewport.width, viewport.height);

	// Setup for testing pixel_to_viewport
	t_window window = {.width = width, .height = height};
	t_vec viewport_point = pixel_to_viewport(width / 2, height / 2, &viewport, &window);
	printf("Viewport coordinates at center (960, 540): (x=%f, y=%f, z=%f)\n", viewport_point.x, viewport_point.y, viewport_point.z);

	// Setup for testing generate_ray
	t_scene scene;
	scene.camera = camera;
	scene.viewport = viewport;
	t_ray ray = generate_ray(&scene, &window, width / 2, height / 2);
	printf("Ray direction: (x=%f, y=%f, z=%f)\n", ray.direction.x, ray.direction.y, ray.direction.z);

	return 0;
}