/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/25 23:58:35 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	translate_sphere(t_mini_rt *rt, t_sphere *sphere)
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

static void	translate_cylinder(t_mini_rt *rt, t_cylinder *cylinder)
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

static void	translate_cone(t_mini_rt *rt, t_cone *cone)
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

void	move_objects(void *param)
{
	t_mini_rt	*rt;
	int			i;

	rt = (t_mini_rt *)param;
	i = -1;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_O)))
	{
		while (++i < rt->scene.objects_nb)
		{
			if (rt->scene.objects[i].type == SPHERE)
				translate_sphere(rt, &(rt->scene.objects[i].data.sphere));
			else if (rt->scene.objects[i].type == CYLINDER)
				translate_cylinder(rt, &(rt->scene.objects[i].data.cylinder));
			else if (rt->scene.objects[i].type == CONE)
				translate_cone(rt, &(rt->scene.objects[i].data.cone));
		}
		render_scene(rt);
	}
}
