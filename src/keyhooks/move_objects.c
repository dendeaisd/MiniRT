/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 21:08:44 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_specific_object(int index, t_mini_rt *rt)
{
	if (rt->scene.objects[index].type == SPHERE)
		translate_sphere(rt, &(rt->scene.objects[index].data.sphere));
	else if (rt->scene.objects[index].type == CYLINDER)
	{
		translate_cylinder(rt, &(rt->scene.objects[index].data.cylinder));
		rotate_cylinder(rt, &(rt->scene.objects[index].data.cylinder));
	}
	else if (rt->scene.objects[index].type == PLANE)
	{
		translate_plane(rt, &(rt->scene.objects[index].data.plane));
		rotate_plane(rt, &(rt->scene.objects[index].data.plane));
	}
	else if (rt->scene.objects[index].type == CONE)
	{
		translate_cone(rt, &(rt->scene.objects[index].data.cone));
		rotate_cone(rt, &(rt->scene.objects[index].data.cone));
	}
	render_scene(rt);
}

static void	move_objects_separately(t_mini_rt *rt, int nb)
{
	if (nb > 0 && mlx_is_key_down(rt->window.mlx, MLX_KEY_1))
		move_specific_object(0, rt);
	else if (nb > 1 && mlx_is_key_down(rt->window.mlx, MLX_KEY_2))
		move_specific_object(1, rt);
	else if (nb > 2 && mlx_is_key_down(rt->window.mlx, MLX_KEY_3))
		move_specific_object(2, rt);
	else if (nb > 3 && mlx_is_key_down(rt->window.mlx, MLX_KEY_4))
		move_specific_object(3, rt);
	else if (nb > 4 && mlx_is_key_down(rt->window.mlx, MLX_KEY_5))
		move_specific_object(4, rt);
	else if (nb > 5 && mlx_is_key_down(rt->window.mlx, MLX_KEY_6))
		move_specific_object(5, rt);
	else if (nb > 6 && mlx_is_key_down(rt->window.mlx, MLX_KEY_7))
		move_specific_object(6, rt);
	else if (nb > 7 && mlx_is_key_down(rt->window.mlx, MLX_KEY_8))
		move_specific_object(7, rt);
	else if (nb > 8 && mlx_is_key_down(rt->window.mlx, MLX_KEY_9))
		move_specific_object(8, rt);
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
			if (rt->scene.objects[i].type != PLANE)
				move_specific_object(i, rt);
		}
	}
	if (rt->scene.objects_nb < 10)
		move_objects_separately(rt, rt->scene.objects_nb);
}
