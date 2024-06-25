/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/25 20:44:46 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	move_camera_v2(t_mini_rt *mini_rt, char direction)
// {
// 	if (direction == 'l')
// 		mini_rt->scene.camera.position.x -= 0.05f;
// 	else if (direction == 'r')
// 		mini_rt->scene.camera.position.x += 0.05f;
// 	else if (direction == 'u')
// 		mini_rt->scene.camera.position.y += 0.05f;
// 	else
// 		mini_rt->scene.camera.position.y -= 0.05f;
// 	render_scene(mini_rt);
// }

// static void	move_camera(void *param)
// {
// 	t_mini_rt	*rt;
	
// 	rt = (t_mini_rt *)param;
// 	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_X))
// 	{
// 		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_EQUAL))
// 			rt->scene.camera.position.x += 0.03f;
// 		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_MINUS))
// 			rt->scene.camera.position.x -= 0.03f;
// 	}
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Y))
// 	{
// 		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_EQUAL))
// 			rt->scene.camera.position.y += 0.03f;
// 		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_MINUS))
// 			rt->scene.camera.position.y -= 0.03f;
// 	}
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
// 	{
// 		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_EQUAL))
// 			rt->scene.camera.position.z += 0.03f;
// 		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_MINUS))
// 			rt->scene.camera.position.z -= 0.03f;
// 	}
// 	render_scene(rt);
// }

static void	move_camera(void *param)
{
	t_mini_rt	*rt;
	
	rt = (t_mini_rt *)param;
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
		rt->scene.camera.position.x += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
		rt->scene.camera.position.x -= 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
		rt->scene.camera.position.y += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
		rt->scene.camera.position.y -= 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
		rt->scene.camera.position.z += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
		rt->scene.camera.position.z -= 0.05f;
	render_scene(rt);
}

static void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*mini_rt;

	if (keydata.action != MLX_PRESS)
		return ;
	mini_rt = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(1, NULL, mini_rt);
	// // FOR THE CAMERA:
	// if (keydata.key == MLX_KEY_UP)
	// 	move_camera_v2(mini_rt, 'u');
	// if (keydata.key == MLX_KEY_DOWN)
	// 	move_camera_v2(mini_rt, 'd');
	// if (keydata.key == MLX_KEY_LEFT)
	// 	move_camera_v2(mini_rt, 'l');
	// if (keydata.key == MLX_KEY_RIGHT)
	// 	move_camera_v2(mini_rt, 'r');

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

void	handle_hooks(t_mini_rt *mini_rt)
{
	mlx_key_hook(mini_rt->window.mlx, ft_keyhook, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, move_camera, mini_rt);
	// mlx_loop_hook(mini_rt->window.mlx, render_scene, mini_rt);
}
