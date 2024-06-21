/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/21 19:10:14 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_camera(t_mini_rt *mini_rt, char direction)
{
	if (direction == 'l')
		mini_rt->scene.camera.position.x -= 0.1f;
	else if (direction == 'r')
		mini_rt->scene.camera.position.x += 0.1f;
	else if (direction == 'u')
		mini_rt->scene.camera.position.y += 0.1f;
	else
		mini_rt->scene.camera.position.y -= 0.1f;
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*mini_rt;

	if (keydata.action != MLX_PRESS)
		return ;
	mini_rt = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(mini_rt, true);
	// FOR THE CAMERA:
	if (keydata.key == MLX_KEY_UP)
		move_camera(mini_rt, 'u');
	if (keydata.key == MLX_KEY_DOWN)
		move_camera(mini_rt, 'd');
	if (keydata.key == MLX_KEY_LEFT)
		move_camera(mini_rt, 'l');
	if (keydata.key == MLX_KEY_RIGHT)
		move_camera(mini_rt, 'r');

	// OR THE OBJECTS:
	// if ((keydata.key == MLX_KEY_W) || (keydata.key == MLX_KEY_UP))
	// 	ft_do_move(game, game->p_x, game->p_y - 1, 'W');
	// if ((keydata.key == MLX_KEY_S) || (keydata.key == MLX_KEY_DOWN))
	// 	ft_do_move(game, game->p_x, game->p_y + 1, 'S');
	// if ((keydata.key == MLX_KEY_A) || (keydata.key == MLX_KEY_LEFT))
	// 	ft_do_move(game, game->p_x - 1, game->p_y, 'A');
	// if ((keydata.key == MLX_KEY_D) || (keydata.key == MLX_KEY_RIGHT))
	// 	ft_do_move(game, game->p_x + 1, game->p_y, 'D');
}

// void	init_hooks(t_mini_rt *mini_rt)
// {
	
// }