/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 21:32:47 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_plane(t_mini_rt *rt, t_plane *plane)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		plane->normal.x += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		plane->normal.x -= 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		plane->normal.y += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		plane->normal.y -= 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		plane->normal.z += 0.05f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		plane->normal.z -= 0.05f;
}

void	rotate_cylinder(t_mini_rt *rt, t_cylinder *cylinder)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		cylinder->axis.x += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		cylinder->axis.x -= 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		cylinder->axis.y += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		cylinder->axis.y -= 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		cylinder->axis.z += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		cylinder->axis.z -= 4.0f;
}

void	rotate_cone(t_mini_rt *rt, t_cone *cone)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		cone->axis.x += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		cone->axis.x -= 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		cone->axis.y += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		cone->axis.y -= 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		cone->axis.z += 4.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		cone->axis.z -= 4.0f;
}
