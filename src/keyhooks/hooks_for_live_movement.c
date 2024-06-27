/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_for_live_movement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/27 02:30:23 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define UNDERLINED_BOLD "\x1B[4;1m"
#define UNDERLINED "\x1B[4m"
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

static void	print_keys_info(void)
{
	printf(UNDERLINED_BOLD "\nAVAILABLE KEYS TO USE" RESET "\n\n");
	printf("You can combine moving the " UNDERLINED "Element" RESET
		" that you want:\n");
	printf("- " BOLD "C" RESET " for " BOLD "Camera" RESET ",\n");
	printf("- " BOLD "L" RESET " for " BOLD "Light" RESET ",\n");
	printf("- " BOLD "O" RESET " for all " BOLD "Objects" RESET
		" at the same time,\n");
	printf("- " BOLD "1, 2, 3," RESET " etc for each object individually,\n\n");
	printf("with either:\n");
	printf("- " BOLD "Arrow Keys,'+','-'" RESET " for " UNDERLINED
		"translation" RESET " in x, y, z axis\n");
	printf("or\n");
	printf("- " BOLD "ADWSEZ" RESET " for " UNDERLINED "rotation" RESET
		" in x, y, z axis, respectively\n\n");
}

void	hooks_for_live_movement(t_mini_rt *mini_rt)
{
	print_keys_info();
	mlx_loop_hook(mini_rt->window.mlx, translate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, rotate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, translate_light, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, move_objects, mini_rt);
}
