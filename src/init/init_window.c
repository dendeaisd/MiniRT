/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:50:37 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/22 04:53:30 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_window(t_mini_rt *mini_rt, int width, int height)
{
	mini_rt->window.mlx = mlx_init(width, height, "miniRT", true);
	if (!mini_rt->window.mlx)
		ft_exit_v2("failed to init mlx", 1, mini_rt->scene.objects, -1);
	mini_rt->window.img = mlx_new_image(mini_rt->window.mlx, width, height);
	if (!mini_rt->window.img)
	{
		mlx_terminate(mini_rt->window.mlx);
		ft_exit_v2("failed to init image", 1, mini_rt->scene.objects, -1);
	}
	mini_rt->window.width = width;
	mini_rt->window.height = height;
}
