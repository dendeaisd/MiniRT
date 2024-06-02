/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/03 01:07:52 by fvoicu           ###   ########.fr       */
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

//test calculate_discriminant
int main() {
	t_ray rays[4] = {
		{{0, 0, -10}, {0, 0, 1}},   // Direct intersection
		{{0, -1, -5}, {0, 0, 1}},   // Tangential intersection
		{{5, 5, -5}, {0, 0, 1}},    // Misses the sphere
		{{0, 0, 0}, {0, 1, 0}}      // Originates inside
	};
	t_sphere sphere = {{0, 0, 0}, 2.0, {255, 0, 0}};

	for (int i = 0; i < 4; i++) {
		float discriminant = calculate_discriminant(&rays[i], &sphere);
		printf("Test Case %d: Discriminant = %f\n", i+1, discriminant);
	}

	//ray originating on the sphere surface and pointing outward
	t_ray ray_surface = {{1, 0, 0}, {1, 0, 0}};
	float discriminant_surface = calculate_discriminant(&ray_surface, &sphere);
	printf("Test Case 5: Discriminant = %f (on surface, pointing out)\n", discriminant_surface);

	return 0;
}
