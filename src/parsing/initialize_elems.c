/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_elems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/16 17:53:21 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
*	@brief Checks the r, g, b values of the color and accepts only integer values
*	in the range [0-255]. Rejects negative numbers or floats and protects from
*	overflow in ft_atoi.
*	@param color_arr: the array of the three strings for the r,g,b values.
*	@returns true: if the the three r,g,b values do NOT meet the requirements for
*	valid color.
*/
bool	invalid_color(char **color_arr)
{
	int	i;
	int	tmp;

	i = -1;
	while (++i < 3)
	{
		if (ft_strchr(color_arr[i], '.') || color_arr[i][0] == '-')
			return (true);
		tmp = ft_atoi(color_arr[i]);
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
void	init_amb_light(char **info, t_scene *scene, char **map_2d)
{
	float	ratio;

	if (array_has_only_numbers(info + 1) == false) // +1 because the index 0 is the identifier (A, C, L)
		ft_exit_miniRT("invalid input for Ambient Lightning", map_2d, info, scene);

	ratio = ft_atof(info[1]);
	if (ratio < 0 || ratio > 1)
		ft_exit_miniRT("ambient lightning must have a ratio between 0.0 and 1.0", map_2d, info, scene);

	scene->ambilight.ratio = ratio;
	if (invalid_color(info + 2))
		ft_exit_miniRT("invalid color for Ambient lightning", map_2d, info, scene);

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
		ft_exit_miniRT("invalid input for Camera", map_2d, info, scene);
	scene->camera.position.x = ft_atof(info[1]);
	scene->camera.position.y = ft_atof(info[2]);
	scene->camera.position.z = ft_atof(info[3]);
	
	int i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_miniRT("camera must have orientation of x, y and z in the range of -1 to 1", map_2d, info, scene);
	}
	scene->camera.orientation.x = ft_atof(info[4]);
	scene->camera.orientation.y = ft_atof(info[5]);
	scene->camera.orientation.z = ft_atof(info[6]);

	if (ft_atof(info[7]) < 0 || ft_atof(info[7]) > 180)
		ft_exit_miniRT("camera must have a field of view in range of 0 to 180 degrees", map_2d, info, scene);
	scene->camera.fov = ft_atof(info[7]);
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
		ft_exit_miniRT("invalid input for Light", map_2d, info, scene);
	scene->light.position.x = ft_atof(info[1]);
	scene->light.position.y = ft_atof(info[2]);
	scene->light.position.z = ft_atof(info[3]);
	
	brightness = ft_atof(info[4]);
	if (brightness < 0 || brightness > 1)
		ft_exit_miniRT("light must have a brightness ratio between 0.0 and 1.0", map_2d, info, scene);
	scene->light.brightness = brightness;

	if (ft_2darray_size(info) == 5) //mandatory part that has no color:
		scene->light.color = (t_color){255, 255, 255}; //sets the color to white, if no values are provided
	else
	{
		if (invalid_color(info + 5))
			ft_exit_miniRT("invalid color for Light", map_2d, info, scene);
		scene->light.color.r = ft_atoi(info[5]);
		scene->light.color.g = ft_atoi(info[6]);
		scene->light.color.b = ft_atoi(info[7]);
	}
}

void	add_sphere(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_miniRT("invalid input for sphere", map_2d, info, scene);
	scene->objects[obj_index].type = SPHERE;
	scene->objects[obj_index].data.sphere.center.x = ft_atof(info[1]);
	scene->objects[obj_index].data.sphere.center.y = ft_atof(info[2]);
	scene->objects[obj_index].data.sphere.center.z = ft_atof(info[3]);
	scene->objects[obj_index].data.sphere.diameter = ft_atof(info[4]);

	if (invalid_color(info + 5))
		ft_exit_miniRT("invalid color for sphere", map_2d, info, scene);
	scene->objects[obj_index].data.sphere.color.r = ft_atof(info[5]);
	scene->objects[obj_index].data.sphere.color.g = ft_atof(info[6]);
	scene->objects[obj_index].data.sphere.color.b = ft_atof(info[7]);
}

void	add_plane(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_miniRT("invalid input for plane", map_2d, info, scene);
	scene->objects[obj_index].type = PLANE;
	// x,y,z coordinates of a point in the plane:
	scene->objects[obj_index].data.plane.point.x = ft_atof(info[1]);
	scene->objects[obj_index].data.plane.point.y = ft_atof(info[2]);
	scene->objects[obj_index].data.plane.point.z = ft_atof(info[3]);
	// x,y,z of the 3d normalized normal vector in range [-1,1]:
	i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_miniRT("plane must have x, y, z coordinates of 3d normalized normal vector in range [-1,1]", map_2d, info, scene);
	}
	scene->objects[obj_index].data.plane.normal.x = ft_atof(info[4]);
	scene->objects[obj_index].data.plane.normal.y = ft_atof(info[5]);
	scene->objects[obj_index].data.plane.normal.z = ft_atof(info[6]);
	// color of the plane:
	if (invalid_color(info + 7))
		ft_exit_miniRT("invalid color for plane", map_2d, info, scene);
	scene->objects[obj_index].data.plane.color.r = ft_atof(info[7]);
	scene->objects[obj_index].data.plane.color.g = ft_atof(info[8]);
	scene->objects[obj_index].data.plane.color.b = ft_atof(info[9]);
}

void	add_cylinder(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_miniRT("invalid input for cylinder", map_2d, info, scene);
	scene->objects[obj_index].type = CYLINDER;
	//x,y,z of the center of the cylinder:
	scene->objects[obj_index].data.cylinder.center.x = ft_atof(info[1]);
	scene->objects[obj_index].data.cylinder.center.y = ft_atof(info[2]);
	scene->objects[obj_index].data.cylinder.center.z = ft_atof(info[3]);
	//3d normalized vector of axis of the cylinder:
	i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_miniRT("cylinder must have x, y, z coordinates of 3d normalized vector of axis in range [-1,1]", map_2d, info, scene);
	}
	scene->objects[obj_index].data.cylinder.axis.x = ft_atof(info[4]);
	scene->objects[obj_index].data.cylinder.axis.y = ft_atof(info[5]);
	scene->objects[obj_index].data.cylinder.axis.z = ft_atof(info[6]);
	//cylinder diameter:
	scene->objects[obj_index].data.cylinder.diameter = ft_atof(info[7]);
	//cylinder height:
	scene->objects[obj_index].data.cylinder.height = ft_atof(info[8]);
	// color of the cylinder:
	if (invalid_color(info + 9))
		ft_exit_miniRT("invalid color for cylinder", map_2d, info, scene);
	scene->objects[obj_index].data.cylinder.color.r = ft_atof(info[9]);
	scene->objects[obj_index].data.cylinder.color.g = ft_atof(info[10]);
	scene->objects[obj_index].data.cylinder.color.b = ft_atof(info[11]);
}
