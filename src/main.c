/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/21 18:21:18 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void check_leaks(void)
{
	system("leaks miniRT");
}

void print_obj_data(t_object *obj)
{
	switch (obj->type)
	{
		case SPHERE:
			printf("center: %f,", obj->data.sphere.center.x);
			printf("%f,", obj->data.sphere.center.y);
			printf("%f\n", obj->data.sphere.center.z);
			printf("center: %f,", obj->data.sphere.center.x);
			printf("%f,", obj->data.sphere.center.y);
			printf("%f\n", obj->data.sphere.center.z);
			printf("Diameter: %f",obj->data.sphere.diameter);
			break;
		default:
			printf("Object was not initialized.\n");
	}
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	atexit(check_leaks); //! to be removed later
	if (argc != 2)
		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene);
	//from now on, the only thing from parsing that needs to be freed is the 'mini_rt->scene->objects' pointer
	init_window(&mini_rt, WIDTH, HEIGHT);
	// print_obj_data(mini_rt.scene.objects);
	render_scene(&mini_rt);
	mlx_key_hook(mini_rt.window.mlx, &ft_keyhook, &mini_rt);
	mlx_loop(mini_rt.window.mlx);
	cleanup_and_exit(&mini_rt, false);
	return (EXIT_SUCCESS);
}
