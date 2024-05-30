/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_miniRT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:01:20 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/31 00:31:15 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_mini_rt	*init_mini_rt(int width, int height)
{
	t_mini_rt	*mini_rt;

	mini_rt = malloc(sizeof(mini_rt));
	if (!mini_rt)
		return (NULL);
	mini_rt->window = init_window(width, height);
	if (!mini_rt->window)
		return (free(mini_rt), NULL);
	mini_rt->scene = init_scene();
	return (mini_rt);
}

void	destroy_mini_rt(t_mini_rt *mini_rt)
{
	if (mini_rt)
	{
		destroy_window(mini_rt->window);
		destroy_scene(mini_rt->scene);
		free(mini_rt);
	}
}
