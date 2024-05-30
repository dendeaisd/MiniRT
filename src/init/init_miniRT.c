/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_miniRT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:01:20 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 23:43:05 by fvoicu           ###   ########.fr       */
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
	//same for scene
	return (mini_rt);
}

void	destroy_mini_rt(t_mini_rt *mini_rt)
{
	if (mini_rt)
	{
		//same for scene
		destroy_window(mini_rt->window);
		free(mini_rt);
	}
}