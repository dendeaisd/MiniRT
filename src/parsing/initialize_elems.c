/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_elems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 19:23:10 by mevangel         ###   ########.fr       */
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
		tmp = ft_atoi(color_arr[i]);
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
void	init_amb_light(char **info, t_mini_rt *mini_rt)
{
	float	ratio;

	if (array_has_only_numbers(info + 1) == false) // +1 because the index 0 is the identifier (A, C, L)
		ft_exit_miniRT("invalid input for Ambient Lightning", 0, info, mini_rt);

	ratio = (float)ft_atof(info[1]);
	if (ratio < 0 || ratio > 1)
		ft_exit_miniRT("ambient lightning must have a ratio between 0.0 and 1.0", 0, info, mini_rt);

	mini_rt->scene.ambilight.ratio = ratio;
	if (invalid_color(info + 2))
		ft_exit_miniRT("invalid color for Ambient lightning", 0, info, mini_rt);

	mini_rt->scene.ambilight.color.r = ft_atoi(info[2]);
	mini_rt->scene.ambilight.color.g = ft_atoi(info[3]);
	mini_rt->scene.ambilight.color.b = ft_atoi(info[4]);
}


/*
	C	-50,0,20			0,0,1.0		70
∗	x,y,z coordinates of the view point: -50.0,0,20
∗	3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
∗	FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
void	init_camera(char **info, t_mini_rt *mini_rt)
{
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_miniRT("invalid input for Camera", 0, info, mini_rt);
	mini_rt->scene.camera.position.x = (float)ft_atof(info[1]);
	mini_rt->scene.camera.position.y = (float)ft_atof(info[2]);
	mini_rt->scene.camera.position.z = (float)ft_atof(info[3]);
	
	int i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_miniRT("camera must have orientation of x, y and z in the range of -1 to 1", 0, info, mini_rt);
	}
	mini_rt->scene.camera.orientation.x = (float)ft_atof(info[4]);
	mini_rt->scene.camera.orientation.y = (float)ft_atof(info[5]);
	mini_rt->scene.camera.orientation.z = (float)ft_atof(info[6]);

	if (ft_atof(info[7]) < 0 || ft_atof(info[7]) > 180)
		ft_exit_miniRT("camera must have a field of view in range of 0 to 180 degrees", 0, info, mini_rt);
	mini_rt->scene.camera.fov = (float)ft_atof(info[7]);
}
