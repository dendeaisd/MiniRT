/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/10 18:56:33 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_obj_data(t_object *obj)
{
	switch (obj->type)
	{
		case SPHERE:
			printf("Diameter: %f",obj->data.sphere.diameter);
			break;
		default:
			printf("Object was not initialized.\n");
	}
}

int	main(void)
{
	t_mini_rt	*mini_rt;

	mini_rt = init_mini_rt(WIDTH, HEIGHT); 
	if (!mini_rt)
		return (fprintf(stderr, "Failed to init miniRT\n"), \
				EXIT_FAILURE);
	printf("width : %d\n", mini_rt->window->width);		
	printf("height : %d\n", mini_rt->window->height);
	render_scene(mini_rt);
	printf("fov : %f\n", mini_rt->scene->camera.fov);
	printf("ratio : %f\n", mini_rt->scene->camera.ratio);
	printf("vp_width : %f\n", mini_rt->scene->camera.viewport.width);
	printf("vp_height : %f\n", mini_rt->scene->camera.viewport.height);
	mlx_loop(mini_rt->window->mlx);
	print_obj_data(mini_rt->scene->objects);
	destroy_mini_rt(mini_rt);
	return (EXIT_SUCCESS);
}