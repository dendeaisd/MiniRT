/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:50:37 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/26 15:37:47 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_window(t_mini_rt *mini_rt, bool hd)
{
	int	width;
	int height;
	
	if (hd == true)
	{
		width = HD_WIDTH;
		height = HD_HEIGHT;
	}
	else
	{
		width = WIDTH;
		height = HEIGHT;
	}
	mini_rt->window.mlx = mlx_init(width, height, "miniRT", true);
	if (!mini_rt->window.mlx)
		cleanup_and_exit(2, "failed to init mlx", mini_rt);
	mini_rt->window.img = mlx_new_image(mini_rt->window.mlx, width, height);
	if (!mini_rt->window.img)
		cleanup_and_exit(2, "failed to init window image", mini_rt);
	mini_rt->window.width = width;
	mini_rt->window.height = height;
}
