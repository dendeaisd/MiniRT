/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:50:11 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 19:10:46 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//TO DO: implement a better way to manage the object allocation/initiation
//		 in init_scene	

// static void	fv_init_camera(t_camera *camera, t_vec position, \
// 						t_vec orientation, float fov);
// static void	fv_init_light(t_light *light, t_vec position, \
// 						float brightness);
// static void	fv_init_ambilight(t_ambilight *ambilight, \
// 							float ratio, t_vec color);

// t_scene	*init_scene(void)
// {
// 	static t_init_array	init_array = {
// 		.func = {init_sphere, init_plane, init_cylinder}};
// 	t_scene				*scene;

// 	scene = malloc(sizeof(t_scene));
// 	if (!scene)
// 		return (NULL);
// 	fv_init_camera(&scene->camera, (t_vec){-50, 0, 0}, \
// 				(t_vec){0, 0, 1}, 70.f);
// 	fv_init_light(&scene->light, (t_vec){-40, 50, 0}, 0.6);
// 	fv_init_ambilight(&scene->ambilight, 0.2, \
// 				(t_vec){255, 255, 255});
// 	scene->objects_nb = 1;
// 	scene->objects = malloc(sizeof(t_object) * scene->objects_nb);
// 	t_sphere	sphere_params = {
// 		.center = (t_vec){0, 0, 20.6},
// 		.diameter = 12.6,
// 		.color = (t_color){10, 0, 255}
// 	};
// 	init_object(SPHERE, &scene->objects[0], &sphere_params, &init_array);
// 	return (scene);
// }

// void	destroy_scene(t_scene *scene)
// {
// 	if (scene)
// 	{
// 		if (scene->objects)
// 			free(scene->objects);
// 		free(scene);
// 	}
// }

// static void	fv_init_camera(t_camera *camera, t_vec position, \
// 						t_vec orientation, float fov)
// {
// 	camera->position = position;
// 	camera->orientation = orientation;
// 	camera->fov = fov;
// }

// static void	fv_init_light(t_light *light, t_vec position, \
// 						float brightness)
// {
// 	light->position = position;
// 	light->brightness = brightness;
// }

// static void	fv_init_ambilight(t_ambilight *ambilight, \
// 							float ratio, t_vec color)
// {
// 	ambilight->ratio = ratio;
// 	ambilight->color = color;
// }
