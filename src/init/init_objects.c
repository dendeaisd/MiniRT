/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/27 08:19:01 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	add_sphere(int idx, char **info, t_scene *scene, char **map2)
{
	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for sphere", map2, info, scene);
	scene->objects[idx].type = SPHERE;
	scene->objects[idx].data.sphere.center.x = ft_atof(info[1]);
	scene->objects[idx].data.sphere.center.y = ft_atof(info[2]);
	scene->objects[idx].data.sphere.center.z = ft_atof(info[3]);
	if (scene->objects[idx].data.sphere.center.z == 0)
		scene->objects[idx].data.sphere.center.z += 10;
	scene->objects[idx].data.sphere.diameter = ft_atof(info[4]);
	if (invalid_color(info + 5))
		ft_exit_mini_rt("invalid color for sphere", map2, info, scene);
	scene->objects[idx].data.sphere.color.r = ft_atof(info[5]);
	scene->objects[idx].data.sphere.color.g = ft_atof(info[6]);
	scene->objects[idx].data.sphere.color.b = ft_atof(info[7]);
}

void	add_plane(int idx, char **info, t_scene *scene, char **map2)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for plane", map2, info, scene);
	scene->objects[idx].type = PLANE;
	scene->objects[idx].data.plane.point.x = ft_atof(info[1]);
	scene->objects[idx].data.plane.point.y = ft_atof(info[2]);
	scene->objects[idx].data.plane.point.z = ft_atof(info[3]);
	if (scene->objects[idx].data.plane.point.z == 0)
		scene->objects[idx].data.plane.point.z += 0;
	i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt("plane must have normal(x, y, z) vector"
				" in range [-1,1]", map2, info, scene);
	}
	scene->objects[idx].data.plane.normal.x = ft_atof(info[4]);
	scene->objects[idx].data.plane.normal.y = ft_atof(info[5]);
	scene->objects[idx].data.plane.normal.z = ft_atof(info[6]);
	if (invalid_color(info + 7))
		ft_exit_mini_rt("invalid color for plane", map2, info, scene);
	scene->objects[idx].data.plane.color.r = ft_atof(info[7]);
	scene->objects[idx].data.plane.color.g = ft_atof(info[8]);
	scene->objects[idx].data.plane.color.b = ft_atof(info[9]);
}

void	add_cylinder(int idx, char **info, t_scene *scene, char **map2)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for cylinder", map2, info, scene);
	scene->objects[idx].type = CYLINDER;
	scene->objects[idx].data.cylinder.center.x = ft_atof(info[1]);
	scene->objects[idx].data.cylinder.center.y = ft_atof(info[2]);
	scene->objects[idx].data.cylinder.center.z = ft_atof(info[3]);
	if (scene->objects[idx].data.cylinder.center.z == 0)
		scene->objects[idx].data.plane.point.z += 10;
	i = 3;
	while (++i < 7)
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt("cylinder must have axis(x, y, z) in "
				"range [-1,1]", map2, info, scene);
	scene->objects[idx].data.cylinder.axis.x = ft_atof(info[4]);
	scene->objects[idx].data.cylinder.axis.y = ft_atof(info[5]);
	scene->objects[idx].data.cylinder.axis.z = ft_atof(info[6]);
	scene->objects[idx].data.cylinder.diameter = ft_atof(info[7]);
	scene->objects[idx].data.cylinder.height = ft_atof(info[8]);
	if (invalid_color(info + 9))
		ft_exit_mini_rt("invalid color for cylinder", map2, info, scene);
	scene->objects[idx].data.cylinder.color.r = ft_atof(info[9]);
	scene->objects[idx].data.cylinder.color.g = ft_atof(info[10]);
	scene->objects[idx].data.cylinder.color.b = ft_atof(info[11]);
}

void	add_cone(int idx, char **info, t_scene *scene, char **map2)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for cone", map2, info, scene);
	scene->objects[idx].type = CONE;
	scene->objects[idx].data.cone.center.x = ft_atof(info[1]);
	scene->objects[idx].data.cone.center.y = ft_atof(info[2]);
	scene->objects[idx].data.cone.center.z = ft_atof(info[3]);
	if (scene->objects[idx].data.cone.center.z == 0)
		scene->objects[idx].data.cone.center.z += 10;
	i = 3;
	while (++i < 7)
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt("cylinder must have axis(x, y, z) in "
				"range [-1,1]", map2, info, scene);
	scene->objects[idx].data.cone.axis.x = ft_atof(info[4]);
	scene->objects[idx].data.cone.axis.y = ft_atof(info[5]);
	scene->objects[idx].data.cone.axis.z = ft_atof(info[6]);
	scene->objects[idx].data.cone.diameter = ft_atof(info[7]);
	scene->objects[idx].data.cone.height = ft_atof(info[8]);
	if (invalid_color(info + 9))
		ft_exit_mini_rt("invalid color for cone", map2, info, scene);
	scene->objects[idx].data.cone.color.r = ft_atof(info[9]);
	scene->objects[idx].data.cone.color.g = ft_atof(info[10]);
	scene->objects[idx].data.cone.color.b = ft_atof(info[11]);
}
