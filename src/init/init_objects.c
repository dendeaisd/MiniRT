/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/25 06:21:58 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	add_sphere(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for sphere", map_2d, info, scene);
	scene->objects[obj_index].type = SPHERE;
	scene->objects[obj_index].data.sphere.center.x = ft_atof(info[1]);
	scene->objects[obj_index].data.sphere.center.y = ft_atof(info[2]);
	scene->objects[obj_index].data.sphere.center.z = ft_atof(info[3]);
	scene->objects[obj_index].data.sphere.diameter = ft_atof(info[4]);
	if (invalid_color(info + 5))
		ft_exit_mini_rt("invalid color for sphere", map_2d, info, scene);
	scene->objects[obj_index].data.sphere.color.r = ft_atof(info[5]);
	scene->objects[obj_index].data.sphere.color.g = ft_atof(info[6]);
	scene->objects[obj_index].data.sphere.color.b = ft_atof(info[7]);
}

void	add_plane(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for plane", map_2d, info, scene);
	scene->objects[obj_index].type = PLANE;
	scene->objects[obj_index].data.plane.point.x = ft_atof(info[1]);
	scene->objects[obj_index].data.plane.point.y = ft_atof(info[2]);
	scene->objects[obj_index].data.plane.point.z = ft_atof(info[3]);
	i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt(\
			"plane must have normal(x, y, z) vector in range [-1,1]", \
				map_2d, info, scene);
	}
	scene->objects[obj_index].data.plane.normal.x = ft_atof(info[4]);
	scene->objects[obj_index].data.plane.normal.y = ft_atof(info[5]);
	scene->objects[obj_index].data.plane.normal.z = ft_atof(info[6]);
	if (invalid_color(info + 7))
		ft_exit_mini_rt("invalid color for plane", map_2d, info, scene);
	scene->objects[obj_index].data.plane.color.r = ft_atof(info[7]);
	scene->objects[obj_index].data.plane.color.g = ft_atof(info[8]);
	scene->objects[obj_index].data.plane.color.b = ft_atof(info[9]);
}

void	add_cylinder(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for cylinder", map_2d, info, scene);
	scene->objects[obj_index].type = CYLINDER;
	scene->objects[obj_index].data.cylinder.center.x = ft_atof(info[1]);
	scene->objects[obj_index].data.cylinder.center.y = ft_atof(info[2]);
	scene->objects[obj_index].data.cylinder.center.z = ft_atof(info[3]);
	i = 3;
	while (++i < 7)
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt(\
			"cylinder must have axis(x, y, z) in range [-1,1]", \
				map_2d, info, scene);
	scene->objects[obj_index].data.cylinder.axis.x = ft_atof(info[4]);
	scene->objects[obj_index].data.cylinder.axis.y = ft_atof(info[5]);
	scene->objects[obj_index].data.cylinder.axis.z = ft_atof(info[6]);
	scene->objects[obj_index].data.cylinder.diameter = ft_atof(info[7]);
	scene->objects[obj_index].data.cylinder.height = ft_atof(info[8]);
	if (invalid_color(info + 9))
		ft_exit_mini_rt("invalid color for cylinder", map_2d, info, scene);
	scene->objects[obj_index].data.cylinder.color.r = ft_atof(info[9]);
	scene->objects[obj_index].data.cylinder.color.g = ft_atof(info[10]);
	scene->objects[obj_index].data.cylinder.color.b = ft_atof(info[11]);
}

void	add_cone(int obj_index, char **info, t_scene *scene, char **map_2d)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for cone", map_2d, info, scene);
	scene->objects[obj_index].type = CONE;
	scene->objects[obj_index].data.cone.center.x = ft_atof(info[1]);
	scene->objects[obj_index].data.cone.center.y = ft_atof(info[2]);
	scene->objects[obj_index].data.cone.center.z = ft_atof(info[3]);
	i = 3;
	while (++i < 7)
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt(\
			"cylinder must have axis(x, y, z) in range [-1,1]", \
				map_2d, info, scene);
	scene->objects[obj_index].data.cone.axis.x = ft_atof(info[4]);
	scene->objects[obj_index].data.cone.axis.y = ft_atof(info[5]);
	scene->objects[obj_index].data.cone.axis.z = ft_atof(info[6]);
	scene->objects[obj_index].data.cone.diameter = ft_atof(info[7]);
	scene->objects[obj_index].data.cone.height = ft_atof(info[8]);
	if (invalid_color(info + 9))
		ft_exit_mini_rt("invalid color for cone", map_2d, info, scene);
	scene->objects[obj_index].data.cone.color.r = ft_atof(info[9]);
	scene->objects[obj_index].data.cone.color.g = ft_atof(info[10]);
	scene->objects[obj_index].data.cone.color.b = ft_atof(info[11]);
}
