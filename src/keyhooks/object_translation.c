/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 20:54:29 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translate_sphere(t_mini_rt *rt, t_sphere *sphere)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
		sphere->center.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
		sphere->center.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
		sphere->center.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
		sphere->center.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
		sphere->center.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
		sphere->center.z -= 1.0f;
}

void	translate_plane(t_mini_rt *rt, t_plane *plane)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
		plane->point.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
		plane->point.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
		plane->point.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
		plane->point.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
		plane->point.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
		plane->point.z -= 1.0f;
}

void	translate_cylinder(t_mini_rt *rt, t_cylinder *cylinder)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
		cylinder->center.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
		cylinder->center.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
		cylinder->center.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
		cylinder->center.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
		cylinder->center.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
		cylinder->center.z -= 1.0f;
}

void	translate_cone(t_mini_rt *rt, t_cone *cone)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_RIGHT))
		cone->center.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_LEFT))
		cone->center.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_UP))
		cone->center.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_DOWN))
		cone->center.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_ADD))
		cone->center.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_KP_SUBTRACT))
		cone->center.z -= 1.0f;
}
