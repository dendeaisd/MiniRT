/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/18 22:26:31 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Example of Ambient Lightning Formatting:
	A   0.2   255,255,255
∗	identifier: A
∗	ambient lighting ratio in range [0.0,1.0]: 0.2
∗	R,G,B colors in range [0-255]: 255, 255, 255
*/
void	init_amb_light(char **info, t_scene *scene, char **map_2d)
{
	float	ratio;

	if (array_has_only_numbers(info + 1) == false) // +1 because the index 0 is the identifier (A, C, L)
		ft_exit_mini_rt("invalid input for Ambient Lightning", map_2d, info, scene);

	ratio = ft_atof(info[1]);
	if (ratio < 0 || ratio > 1)
		ft_exit_mini_rt("ambient lightning must have a ratio between 0.0 and 1.0", map_2d, info, scene);

	scene->ambilight.ratio = ratio;
	if (invalid_color(info + 2))
		ft_exit_mini_rt("invalid color for Ambient lightning", map_2d, info, scene);

	scene->ambilight.color.r = ft_atoi(info[2]);
	scene->ambilight.color.g = ft_atoi(info[3]);
	scene->ambilight.color.b = ft_atoi(info[4]);
}


/*
	C	-50,0,20			0,0,1.0		70
∗	x,y,z coordinates of the view point: -50.0,0,20
∗	3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
∗	FOV : Horizontal field of view in degrees in range [0,180]: 70
*/
void	init_camera(char **info, t_scene *scene, char **map_2d)
{
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for Camera", map_2d, info, scene);
	scene->camera.position.x = ft_atof(info[1]);
	scene->camera.position.y = ft_atof(info[2]);
	scene->camera.position.z = ft_atof(info[3]);
	
	int i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt("camera must have orientation of x, y and z in the range of -1 to 1", map_2d, info, scene);
	}
	scene->camera.orientation.x = ft_atof(info[4]);
	scene->camera.orientation.y = ft_atof(info[5]);
	scene->camera.orientation.z = ft_atof(info[6]);

	if (ft_atof(info[7]) < 0 || ft_atof(info[7]) > 180)
		ft_exit_mini_rt("camera must have a field of view in range of 0 to 180 degrees", map_2d, info, scene);
	scene->camera.fov = ft_atof(info[7]);
	
	// The 4 additional lines Flavia had in her init_scene:
	scene->camera.orientation = vec_mul(scene->camera.orientation, -1);
	scene->camera.ratio = 0.f;
	scene->camera.viewport.width = 0.f;
	scene->camera.viewport.height = 0.f;
}

/*
*	Example: L   -40.0, 50.0, 0.0   0.6  ( 10,0,255 )
*	x,y,z coordinates of the light point
*	light brightness ratio in range [0.0,1.0] -> now 0.6
*	( bonus part: R,G,B colors in range 0-255 )
*/
void	init_light(char **info, t_scene *scene, char **map_2d)
{
	float	brightness;
	
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for Light", map_2d, info, scene);
	scene->light.position.x = ft_atof(info[1]);
	scene->light.position.y = ft_atof(info[2]);
	scene->light.position.z = ft_atof(info[3]);
	
	brightness = ft_atof(info[4]);
	if (brightness < 0 || brightness > 1)
		ft_exit_mini_rt("light must have a brightness ratio between 0.0 and 1.0", map_2d, info, scene);
	scene->light.brightness = brightness;

	if (ft_2darray_size(info) == 5) //mandatory part that has no color:
		scene->light.color = (t_color){255, 255, 255}; //sets the color to white, if no values are provided
	else
	{
		if (invalid_color(info + 5))
			ft_exit_mini_rt("invalid color for Light", map_2d, info, scene);
		scene->light.color.r = ft_atoi(info[5]);
		scene->light.color.g = ft_atoi(info[6]);
		scene->light.color.b = ft_atoi(info[7]);
	}
}
