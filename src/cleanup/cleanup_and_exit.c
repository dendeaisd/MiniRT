/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:23:06 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/17 22:26:19 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cleanup_and_exit(int fd_to, char *message, t_mini_rt *mini_rt)
{
	if (fd_to == 1)
		ft_putendl_fd("\x1B[32mminiRT closed successfully!\x1B[0m", 1);
	else if (fd_to == 2)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putendl_fd(message, 2);
	}
	if (mini_rt->window.img)
		mlx_delete_image(mini_rt->window.mlx, mini_rt->window.img);
	if (mini_rt->window.mlx)
		mlx_terminate(mini_rt->window.mlx);
	if (mini_rt->scene.objects)
		free(mini_rt->scene.objects);
	if (mini_rt->scene.lights)
		free(mini_rt->scene.lights);
	exit(EXIT_SUCCESS);
}
