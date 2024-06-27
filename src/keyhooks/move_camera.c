/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/27 05:26:18 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translate_camera(void *param)
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

void	rotate_camera(void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_C)))
	{
		if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
			rt->scene.camera.orientation.x -= 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
			rt->scene.camera.orientation.x += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
			rt->scene.camera.orientation.y += 0.05f;
		else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
			rt->scene.camera.orientation.y -= 0.05f;
	}
}
