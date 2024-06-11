/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaviav <flaviav@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 02:04:11 by flaviav          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_obj_data(t_object *obj)
{
	switch (obj->type)
	{
		case SPHERE:
			printf("center: %f,", obj->data.sphere.center.x);
			printf("%f,", obj->data.sphere.center.y);
			printf("%f\n", obj->data.sphere.center.z);
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
	print_obj_data(mini_rt->scene->objects);
	if (!mini_rt)
		return (fprintf(stderr, "Failed to init miniRT\n"), \
				EXIT_FAILURE);
	render_scene(mini_rt);
	printf("camera : %f %f %f\n", mini_rt->scene->camera.position.x, mini_rt->scene->camera.position.y, mini_rt->scene->camera.position.z);
	mlx_loop(mini_rt->window->mlx);
	destroy_mini_rt(mini_rt);
	return (EXIT_SUCCESS);
}