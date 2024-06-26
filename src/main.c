/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 16:21:11 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	if (argc > 3 || argc < 2)
		ft_exit("expected two arguments in the format:"
			" ./miniRT map.rt (HD)", 0);
	open_and_parse_map(argv, &mini_rt.scene);
	if (argc == 3 && !ft_strncmp(argv[2], "HD", 3))
		mini_rt.scene.hd_version = true;
	else
		mini_rt.scene.hd_version = false;
	init_window(&mini_rt, mini_rt.scene.hd_version);
	render_scene(&mini_rt);
	mlx_key_hook(mini_rt.window.mlx, escape, &mini_rt);
	if (mini_rt.scene.hd_version)
		movement_loops(&mini_rt);
	mlx_loop(mini_rt.window.mlx);
	cleanup_and_exit(1, NULL, &mini_rt);
	return (0);
}
