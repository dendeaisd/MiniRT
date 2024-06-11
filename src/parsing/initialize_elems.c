/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_elems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 14:38:59 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	invalid_color(char **color_arr)
{
	int		i;
	double	tmp;

	i = -1;
	while (++i < 3)
	{
		printf("string color[%d]: %s\n", i, color_arr[i]);
		tmp = fv_atof(color_arr[i]);
		printf("color[%d]: %f\n", i, tmp);
		if (tmp < 0 || tmp > 255)
			return (true);
	}
	return (false);
}

/*
Example of Ambient Lightning Formatting:
	A   0.2   255,255,255
∗	identifier: A
∗	ambient lighting ratio in range [0.0,1.0]: 0.2
∗	R,G,B colors in range [0-255]: 255, 255, 255
*/
void	init_amb_light(char **map_2d, char **info, t_mini_rt *mini_rt)
{
	float	ratio;

	ratio = (float)fv_atof(info[1]);
	if (ratio < 0 || ratio > 1)
	{
		fv_free_array(info);
		ft_exit_v4("ambient lightning must have a ratio between 0.0 and 1.0", 0, mini_rt->scene.objects, map_2d);
	}
	mini_rt->scene.ambilight.ratio = ratio;
	if (invalid_color(info + 2))
	{
		fv_free_array(info);
		ft_exit_v4("invalid color for Ambient lightning", 0, mini_rt->scene.objects, map_2d);
	}
	mini_rt->scene.ambilight.color.x = (float)fv_atof(info[2]);
	mini_rt->scene.ambilight.color.y = (float)fv_atof(info[3]);
	mini_rt->scene.ambilight.color.z = (float)fv_atof(info[4]);
}
