/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 00:06:28 by mevangel         ###   ########.fr       */
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
	render_scene(&mini_rt);
	handle_hooks(&mini_rt);
	mlx_loop(mini_rt.window.mlx);
	cleanup_and_exit(1, NULL, &mini_rt);
	return (0);
}
