/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/21 18:57:32 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void	display_img(t_window *window)
{
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}

int	check_intersections(t_ray *ray, t_scene *scene, float *closest_dist)
{
	int		closest_idx;
	bool	hit;
	int		i;
	float	t;

	i = -1;
	*closest_dist = INFINITY;
	closest_idx = -1;
	while (++i < scene->objects_nb)
	{
		hit = false;
		if (scene->objects[i].type == SPHERE)
			hit = intersect_sphere(ray, &scene->objects[i].data.sphere, &t);
		else if (scene->objects[i].type == PLANE)
			hit = intersect_plane(ray, &scene->objects[i].data.plane, &t);
		else if (scene->objects[i].type == CYLINDER)
			hit = intersect_cylinder(ray, &scene->objects[i].data.cylinder, &t);
		if (hit && t < *closest_dist)
		{
			closest_idx = i;
			*closest_dist = t;
		}
	}
	return (closest_idx);
}

//TODO: *too many vars in this function*
void	render_scene(void *param)
{
	t_ray			ray;
	unsigned int	color;
	int				obj_idx;
	float			closest_dist;
	int				i;
	int				j;
	t_mini_rt		*mini_rt;

	mini_rt = param;
	setup_camera(&mini_rt->scene.camera, \
			mini_rt->window.width, mini_rt->window.height);
	j = -1;
	while (++j < mini_rt->window.height)
	{
		i = -1;
		while (++i < mini_rt->window.width)
		{
			ray = generate_ray(&mini_rt->scene, &mini_rt->window, i, j);
			obj_idx = check_intersections(&ray, &mini_rt->scene, &closest_dist);
			if (obj_idx != -1)
				color = get_pixel_color(obj_idx, &mini_rt->scene, \
									ray, closest_dist);
			else
				color = vec_to_color((t_color){0, 0, 0});
			mlx_put_pixel(mini_rt->window.img, i, j, color);
		}
	}
	display_img(&mini_rt->window);
}
