/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:54:35 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/27 03:38:28 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_amb_light(char **info, t_scene *scene, char **map2)
{
	float	ratio;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for Ambient Lightning", \
					map2, info, scene);
	ratio = ft_atof(info[1]);
	if (ratio < 0 || ratio > 1)
		ft_exit_mini_rt(\
		"ambient lightning must have a ratio between 0.0 and 1.0", \
					map2, info, scene);
	scene->ambilight.ratio = ratio;
	if (invalid_color(info + 2))
		ft_exit_mini_rt("invalid color for Ambient lightning", \
					map2, info, scene);
	scene->ambilight.color.r = ft_atoi(info[2]);
	scene->ambilight.color.g = ft_atoi(info[3]);
	scene->ambilight.color.b = ft_atoi(info[4]);
}

void	init_camera(char **info, t_scene *scene, char **map2)
{
	int	i;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for Camera", map2, info, scene);
	scene->camera.position.x = ft_atof(info[1]) / 100;
	scene->camera.position.y = ft_atof(info[2]) / 100;
	scene->camera.position.z = ft_atof(info[3]) / 100;
	i = 3;
	while (++i < 7)
	{
		if (ft_atof(info[i]) < -1 || ft_atof(info[i]) > 1)
			ft_exit_mini_rt(\
			"camera must have orientation in the range  [-1, 1]", \
				map2, info, scene);
	}
	scene->camera.orientation.x = ft_atof(info[4]);
	scene->camera.orientation.y = ft_atof(info[5]);
	scene->camera.orientation.z = ft_atof(info[6]);
	if (ft_atof(info[7]) < 0 || ft_atof(info[7]) > 180)
		ft_exit_mini_rt(\
		"FOV must be in the range [0, 180]", map2, info, scene);
	scene->camera.fov = ft_atof(info[7]);
	scene->camera.ratio = 0.f;
	scene->camera.viewport.width = 0.f;
	scene->camera.viewport.height = 0.f;
}

void	init_light(char **info, t_scene *scene, char **map2)
{
	float	brightness;

	if (array_has_only_numbers(info + 1) == false)
		ft_exit_mini_rt("invalid input for Light", map2, info, scene);
	scene->light.position.x = ft_atof(info[1]);
	scene->light.position.y = ft_atof(info[2]);
	scene->light.position.z = ft_atof(info[3]);
	brightness = ft_atof(info[4]);
	if (brightness < 0 || brightness > 1)
		ft_exit_mini_rt(\
		"light must have a brightness ratio between 0.0 and 1.0", \
			map2, info, scene);
	scene->light.brightness = brightness;
	if (ft_2darray_size(info) == 5)
		scene->light.color = (t_color){255, 255, 255};
	else
	{
		if (invalid_color(info + 5))
			ft_exit_mini_rt("invalid color for Light", map2, info, scene);
		scene->light.color.r = ft_atoi(info[5]);
		scene->light.color.g = ft_atoi(info[6]);
		scene->light.color.b = ft_atoi(info[7]);
	}
}
