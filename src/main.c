/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 20:49:44 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void check_leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	atexit(check_leaks);
	/* ******************* PARSING PART ******************** */
	if (argc != 2)
		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene);
	//from now on, the only thing from parsin that need to be freed is the 'mini_rt->scene->objects' pointer
	// ... execution part ...
	init_window(&mini_rt, WIDTH, HEIGHT);
	// mini_rt.window.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	// if (!mini_rt.window.mlx)
	// 	ft_exit_v2("failed to init mlx", 1, mini_rt.scene.objects, -1);
	// mini_rt.window.img = mlx_new_image(mini_rt.window.mlx, WIDTH, HEIGHT);
	// if (!mini_rt.window.img)
	// {
	// 	mlx_terminate(mini_rt.window.mlx);
	// 	ft_exit_v2("failed to init window image", 1, mini_rt.scene.objects, -1);
	// }

	// render_scene(&mini_rt);
	// mlx_loop(&mini_rt.window->mlx);
	destroy_window(&mini_rt.window);
	free(mini_rt.scene.objects);
	
	return (EXIT_SUCCESS);
}
