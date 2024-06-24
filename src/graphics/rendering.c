/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:53:57 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 04:45:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>
//TODO: too many funcs in file, othewise normed

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
		else if (scene->objects[i].type == CONE)
			hit = intersect_cone(ray, &scene->objects[i].data.cone, &t);
		if (hit && t < *closest_dist)
		{
			closest_idx = i;
			*closest_dist = t;
		}
	}
	return (closest_idx);
}

void	render_pixel(t_mini_rt *mini_rt, int i, int j)
{
	t_ray			ray;
	int				obj_idx;
	float			closest_dist;
	unsigned int	color;

	ray = generate_ray(&mini_rt->scene, &mini_rt->window, i, j);
	obj_idx = check_intersections(&ray, &mini_rt->scene, &closest_dist);
	if (obj_idx != -1)
		color = get_pixel_color(obj_idx, \
			&mini_rt->scene, ray, closest_dist);
	else
		color = vec_to_color((t_color){0, 0, 0});
	mlx_put_pixel(mini_rt->window.img, i, j, color);
}

void	render_rows(t_mini_rt *mini_rt, int start_row, int end_row)
{
	int	i;
	int	j;

	j = start_row;
	while (j < end_row)
	{
		i = -1;
		while (++i < mini_rt->window.mlx->width)
			render_pixel(mini_rt, i, j);
		++j;
	}
}

void	*thread_render(void *arg)
{
	t_thread_data	*data;
	int				rows_per_thread;
	int				start_row;
	int				end_row;

	data = (t_thread_data *)arg;
	rows_per_thread = data->mini_rt->window.mlx->height / data->th_nb;
	start_row = data->th_idx * rows_per_thread;
	if (data->th_idx == data->th_nb - 1)
		end_row = data->mini_rt->window.mlx->height;
	else
		end_row = (data->th_idx + 1) * rows_per_thread;
	render_rows(data->mini_rt, start_row, end_row);
	free(data);
	return (NULL);
}

void	render_scene(t_mini_rt *mini_rt)
{
	const int		threads_nb = 12;
	pthread_t		*threads;
	t_thread_data	*data;
	int				i;

	setup_camera(&mini_rt->scene.camera, \
		mini_rt->window.mlx->width, mini_rt->window.mlx->height);
	threads = (pthread_t *)malloc(threads_nb * sizeof(pthread_t));
	i = -1;
	while (++i < threads_nb)
	{
		data = (t_thread_data *)malloc(sizeof(t_thread_data));
		data->mini_rt = mini_rt;
		data->th_idx = i;
		data->th_nb = threads_nb;
		pthread_create(&threads[i], NULL, thread_render, data);
	}
	i = -1;
	while (++i < threads_nb)
		pthread_join(threads[i], NULL);
	if (mlx_image_to_window(mini_rt->window.mlx, mini_rt->window.img, 0, 0) < 0)
		cleanup_and_exit(2, "failed to display image", mini_rt);
	free(threads); //! we want that!
}
