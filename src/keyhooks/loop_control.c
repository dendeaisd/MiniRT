/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 02:16:19 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	escape(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*mini_rt;

	if (keydata.action != MLX_PRESS)
		return ;
	mini_rt = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(1, NULL, mini_rt);
}

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

static void	translate_light(void *param)
{
	t_mini_rt	*rt;
	
	rt = (t_mini_rt *)param;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_L)))
	{
		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
			rt->scene.light.position.x += 1.5f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
			rt->scene.light.position.x -= 1.5f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
			rt->scene.light.position.y += 1.5f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
			rt->scene.light.position.y -= 1.5f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
			rt->scene.light.position.z -= 1.5f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
			rt->scene.light.position.z += 1.5f;
		render_scene(rt);
	}
}

void	handle_hooks(t_mini_rt *mini_rt)
{
	mlx_key_hook(mini_rt->window.mlx, escape, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, translate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, rotate_camera, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, translate_light, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, move_objects, mini_rt);
	mlx_loop_hook(mini_rt->window.mlx, rotate_objects, mini_rt);
}
