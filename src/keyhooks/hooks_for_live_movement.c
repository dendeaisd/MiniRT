/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_for_live_movement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 21:21:55 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	hooks_for_live_movement(t_mini_rt *mini_rt)
{
	// printing of memo, so that the user knows the keys to use
	mlx_loop_hook(mini_rt->window.mlx, translate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, rotate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, translate_light, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, move_objects, mini_rt);
}
