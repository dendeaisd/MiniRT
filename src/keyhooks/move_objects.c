/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 00:31:58 by mevangel         ###   ########.fr       */
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

static void	move_specific_object(int index, t_mini_rt *rt)
{
	if (rt->scene.objects[index].type == SPHERE)
		translate_sphere(rt, &(rt->scene.objects[index].data.sphere));
	else if (rt->scene.objects[index].type == CYLINDER)
		translate_cylinder(rt, &(rt->scene.objects[index].data.cylinder));
	else if (rt->scene.objects[index].type == CONE)
		translate_cone(rt, &(rt->scene.objects[index].data.cone));
}

static void	move_objects_separately(t_mini_rt *rt)
{
	if (rt->scene.objects_nb > 0 && mlx_is_key_down(rt->window.mlx, MLX_KEY_1))
		move_specific_object(0, rt);
	else if (rt->scene.objects_nb > 1 && mlx_is_key_down(rt->window.mlx, MLX_KEY_2))
		move_specific_object(1, rt);
	else if (rt->scene.objects_nb > 2 && mlx_is_key_down(rt->window.mlx, MLX_KEY_3))
		move_specific_object(2, rt);
	else if (rt->scene.objects_nb > 3 && mlx_is_key_down(rt->window.mlx, MLX_KEY_4))
		move_specific_object(3, rt);
	else if (rt->scene.objects_nb > 4 && mlx_is_key_down(rt->window.mlx, MLX_KEY_5))
		move_specific_object(4, rt);
	else if (rt->scene.objects_nb > 5 && mlx_is_key_down(rt->window.mlx, MLX_KEY_6))
		move_specific_object(5, rt);
	else if (rt->scene.objects_nb > 6 && mlx_is_key_down(rt->window.mlx, MLX_KEY_7))
		move_specific_object(6, rt);
	else if (rt->scene.objects_nb > 7 && mlx_is_key_down(rt->window.mlx, MLX_KEY_8))
		move_specific_object(7, rt);
	else if (rt->scene.objects_nb > 8 && mlx_is_key_down(rt->window.mlx, MLX_KEY_9))
		move_specific_object(8, rt);
	render_scene(rt);
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
			move_specific_object(i, rt);
		render_scene(rt);
	}
	if (rt->scene.objects_nb < 10)
		move_objects_separately(rt);
}
