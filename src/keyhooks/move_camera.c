/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/25 22:24:55 by mevangel         ###   ########.fr       */
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

// static void	move_camera(void *param)
// {
// 	t_mini_rt	*rt;
	
// 	rt = (t_mini_rt *)param;
// 	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
// 		rt->scene.camera.orientation.x += 0.05f;
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
// 		rt->scene.camera.orientation.x -= 0.05f;
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
// 		rt->scene.camera.orientation.y += 0.05f;
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
// 		rt->scene.camera.orientation.y -= 0.05f;
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
// 		rt->scene.camera.position.z -= 0.05f;
// 	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
// 		rt->scene.camera.position.z += 0.05f;
// 	render_scene(rt);
// }

static void	translate_camera(void *param)
{
	t_mini_rt	*rt;
	
	rt = (t_mini_rt *)param;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_C)))
	{
		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
			rt->scene.camera.position.x -= 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
			rt->scene.camera.position.x += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
			rt->scene.camera.position.y -= 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
			rt->scene.camera.position.y += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
			rt->scene.camera.position.z -= 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
			rt->scene.camera.position.z += 0.05f;
		render_scene(rt);
	}
}

static void	rotate_camera(void *param)
{
	t_mini_rt	*rt;
	
	rt = (t_mini_rt *)param;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_V)))
	{
		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
			rt->scene.camera.orientation.x -= 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
			rt->scene.camera.orientation.x += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
			rt->scene.camera.orientation.y += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
			rt->scene.camera.orientation.y -= 0.05f;
		render_scene(rt);
	}
}

static void	escape(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*mini_rt;

	if (keydata.action != MLX_PRESS)
		return ;
	mini_rt = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(1, NULL, mini_rt);
}

void	handle_hooks(t_mini_rt *mini_rt)
{
	mlx_key_hook(mini_rt->window.mlx, escape, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, translate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, rotate_camera, mini_rt);
	// mlx_loop_hook(mini_rt->window.mlx, translate_light, mini_rt);
	// mlx_loop_hook(mini_rt->window.mlx, render_scene, mini_rt);
}
