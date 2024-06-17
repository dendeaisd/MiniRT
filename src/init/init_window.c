/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:50:37 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 23:42:33 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_window	*init_window(int width, int height)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init(width, \
				height, "miniRT", true);
	if (!window->mlx)
		return (free(window), NULL);
	window->img = mlx_new_image(window->mlx, \
				width, height);
	if (!window->img)
		return (mlx_terminate(window->mlx), \
				free(window), NULL);
	window->width = width;
	window->height = height;
	return (window);
}

void	destroy_window(t_window *window)
{
	if (window)
	{
		if (window->img)
			mlx_delete_image(window->mlx, window->img);
		if (window->mlx)
			mlx_terminate(window->mlx);
		free(window);
	}
}
