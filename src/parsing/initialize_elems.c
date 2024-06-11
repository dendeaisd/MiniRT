/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_elems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 17:23:11 by mevangel         ###   ########.fr       */
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
		// printf("string color[%d]: %s\n", i, color_arr[i]);
		tmp = fv_atof(color_arr[i]);
		// printf("color[%d]: %f\n", i, tmp);
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

	if (array_has_only_numbers(info) == false) //if that returns false, the "info" is freed inside that function
		ft_exit_v4("invalid input for Ambient Lightning", 0, mini_rt->scene.objects, map_2d);
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

// static bool	invalid_vector_range(char **vector)
// {
// 	int		i;
// 	double	tmp;

// 	i = -1;
// 	while (++i < 3)
// 	{
// 		// printf("string color[%d]: %s\n", i, color_arr[i]);
// 		tmp = fv_atof(vector[i]);
// 		// printf("color[%d]: %f\n", i, tmp);
// 		if (tmp < 0 || tmp > 255)
// 			return (true);
// 	}
// 	return (false);
// }


/*
	C -50.0,0,20 0,0,1 70
∗	identifier: C
∗	x,y,z coordinates of the view point: -50.0,0,20
∗	3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
∗	FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
void	init_camera(char **map_2d, char **info, t_mini_rt *mini_rt)
{
	//! need to check if the info array is valid. so that i return error for e.g. info[1] = "abc"
	mini_rt->scene.camera.position.x = (float)fv_atof(info[1]);
	mini_rt->scene.camera.position.y = (float)fv_atof(info[2]);
	mini_rt->scene.camera.position.z = (float)fv_atof(info[3]);

	(void)map_2d;
}
