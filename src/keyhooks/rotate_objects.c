/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 03:02:41 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate_plane(t_mini_rt *rt, t_plane *plane)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		plane->normal.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		plane->normal.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		plane->normal.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		plane->normal.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		plane->normal.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		plane->normal.z -= 1.0f;
}

static void	rotate_cylinder(t_mini_rt *rt, t_cylinder *cylinder)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		cylinder->axis.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		cylinder->axis.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		cylinder->axis.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		cylinder->axis.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		cylinder->axis.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		cylinder->axis.z -= 1.0f;
}

static void	rotate_cone(t_mini_rt *rt, t_cone *cone)
{
	if (mlx_is_key_down(rt->window.mlx, MLX_KEY_D))
		cone->axis.x += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_A))
		cone->axis.x -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_W))
		cone->axis.y += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_S))
		cone->axis.y -= 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_E))
		cone->axis.z += 1.0f;
	else if (mlx_is_key_down(rt->window.mlx, MLX_KEY_Z))
		cone->axis.z -= 1.0f;
}

static void	rotate_specific_object(int index, t_mini_rt *rt)
{
	if (rt->scene.objects[index].type == CYLINDER)
		rotate_cylinder(rt, &(rt->scene.objects[index].data.cylinder));
	else if (rt->scene.objects[index].type == PLANE)
		rotate_plane(rt, &(rt->scene.objects[index].data.plane));
	else if (rt->scene.objects[index].type == CONE)
		rotate_cone(rt, &(rt->scene.objects[index].data.cone));
}

static void	rotate_objects_separately(t_mini_rt *rt)
{
	if (rt->scene.objects_nb > 0 && mlx_is_key_down(rt->window.mlx, MLX_KEY_1))
		rotate_specific_object(0, rt);
	else if (rt->scene.objects_nb > 1 && mlx_is_key_down(rt->window.mlx, MLX_KEY_2))
		rotate_specific_object(1, rt);
	else if (rt->scene.objects_nb > 2 && mlx_is_key_down(rt->window.mlx, MLX_KEY_3))
		rotate_specific_object(2, rt);
	else if (rt->scene.objects_nb > 3 && mlx_is_key_down(rt->window.mlx, MLX_KEY_4))
		rotate_specific_object(3, rt);
	else if (rt->scene.objects_nb > 4 && mlx_is_key_down(rt->window.mlx, MLX_KEY_5))
		rotate_specific_object(4, rt);
	else if (rt->scene.objects_nb > 5 && mlx_is_key_down(rt->window.mlx, MLX_KEY_6))
		rotate_specific_object(5, rt);
	else if (rt->scene.objects_nb > 6 && mlx_is_key_down(rt->window.mlx, MLX_KEY_7))
		rotate_specific_object(6, rt);
	else if (rt->scene.objects_nb > 7 && mlx_is_key_down(rt->window.mlx, MLX_KEY_8))
		rotate_specific_object(7, rt);
	else if (rt->scene.objects_nb > 8 && mlx_is_key_down(rt->window.mlx, MLX_KEY_9))
		rotate_specific_object(8, rt);
	render_scene(rt);
}

void	rotate_objects(void *param)
{
	t_mini_rt	*rt;
	int			i;

	rt = (t_mini_rt *)param;
	i = -1;
	if ((mlx_is_key_down(rt->window.mlx, MLX_KEY_R)))
	{
		while (++i < rt->scene.objects_nb)
		{
			if (rt->scene.objects[i].type != PLANE)
				rotate_specific_object(i, rt);
		}
		render_scene(rt);
	}
	if (rt->scene.objects_nb < 10)
		rotate_objects_separately(rt);
}
