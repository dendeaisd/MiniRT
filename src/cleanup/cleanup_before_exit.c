/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:23:06 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/21 17:54:40 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cleanup_and_exit(t_mini_rt *mini_rt, bool do_exit)
{
	if (mini_rt->window.img)
		mlx_delete_image(mini_rt->window.mlx, mini_rt->window.img);
	if (mini_rt->window.mlx)
		mlx_terminate(mini_rt->window.mlx);
	if (mini_rt->scene.objects)
		free(mini_rt->scene.objects);
	if (do_exit == true)
		exit(EXIT_SUCCESS);
}
