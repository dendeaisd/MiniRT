/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 12:25:27 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void	setup_camera(t_camera *camera, int width, int height)
{
	camera->ratio = calc_aspect_ratio(width, height);
	calc_viewport_dim(camera, camera->ratio, \
						&camera->viewport);
}

int	check_intersections(t_ray *ray, t_scene *scene)
{
	int		i;
	float	t;

	i = -1;
	while (++i < scene->objects_nb)
	{
		if (intersect_sphere(ray, &scene->objects[i].data.sphere, &t))
			return (i);
	}
	return (-1);
}

void	display_img(t_window *window)
{
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}

void	render_scene(t_mini_rt *mini_rt)
{
	t_ray			ray;
	unsigned int	color;
	int				obj_idx;
	int				i;
	int				j;

	setup_camera(&mini_rt->scene->camera, \
			mini_rt->window->width, mini_rt->window->height);
	j = -1;
	while (++j < mini_rt->window->height)
	{
		i = -1;
		while (++i < mini_rt->window->width)
		{
			ray = generate_ray(mini_rt->scene, mini_rt->window, i, j);
			obj_idx = check_intersections(&ray, mini_rt->scene);
			color = get_pixel_color(obj_idx, mini_rt->scene);
			mlx_put_pixel(mini_rt->window->img, i, j, color);
		}
	}
	display_img(mini_rt->window);
}
