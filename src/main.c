/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 20:20:38 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	/* ******************* PARSING PART ******************** */
	if (argc != 2)
		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene);
	//from now on, the only thing from parsin that need to be freed is the 'mini_rt->scene->objects' pointer
	// ... execution part ...
	mini_rt.window = init_window(WIDTH, HEIGHT);
	if (!mini_rt.window)
		ft_exit_v2("failed to init window", 1, mini_rt.scene.objects, -1);
	// from now on the 'mini_rt.window' need to be freed
	// render_scene(&mini_rt);
	// mlx_loop(&mini_rt.window->mlx);
	free(mini_rt.scene.objects);
	
	return (EXIT_SUCCESS);
}
