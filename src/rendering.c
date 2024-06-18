/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/18 22:29:50 by fvoicu           ###   ########.fr       */
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

void	display_img(t_window *window)
{
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		fprintf(stderr, "Error displaying image\n");
	}
}

bool	intersect(t_ray *ray, t_object object, float *t)
{
	if (object.type == SPHERE)
		return (intersect_sphere(ray, &object.data.sphere, t));
	else if(object.type == PLANE)
		return (intersect_plane(ray, &object.data.plane, t));
	else if(object.type == CYLINDER)
		return (intersect_cylinder(ray, &object.data.cylinder, t));
	return(false);
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
		hit = intersect(ray, scene->objects[i], &t);
		if (hit && t < *closest_dist)
		{
			closest_idx = i;
			*closest_dist = t;
		}
	}
	return (closest_idx);
}

void	render_scene(t_mini_rt *mini_rt)
{
	t_ray			ray;
	unsigned int	color;
	int				obj_idx;
	float			closest_dist;
	int				i;
	int				j;

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
				color = get_pixel_color(obj_idx, &mini_rt->scene, ray, closest_dist);
			else
				color = vec_to_color((t_color){0, 0, 0});
			mlx_put_pixel(mini_rt->window.img, i, j, color);
		}
	}
	display_img(&mini_rt->window);
}
