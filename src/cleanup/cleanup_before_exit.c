/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_before_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:23:06 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/17 22:26:19 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cleanup_before_exit(t_mini_rt *mini_rt)
{
	if (mini_rt->window.img)
		mlx_delete_image(mini_rt->window.mlx, mini_rt->window.img);
	if (mini_rt->window.mlx)
		mlx_terminate(mini_rt->window.mlx);
	if (mini_rt->scene.objects)
		free(mini_rt->scene.objects);
}
