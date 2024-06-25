/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 19:24:38 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;


	if (argc != 2)
		ft_exit("expected two arguments in the format:"
			" ./miniRT map.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene);

	init_window(&mini_rt, WIDTH, HEIGHT);
	// print_obj_data(mini_rt.scene.objects);
	render_scene(&mini_rt);	
	// mlx_key_hook(mini_rt.window.mlx, &ft_keyhook, &mini_rt);
	// mlx_loop_hook(mini_rt.window.mlx, &render_scene, &mini_rt);
	mlx_loop(mini_rt.window.mlx);
	cleanup_and_exit(1, NULL, &mini_rt);
	return (EXIT_SUCCESS);
}
