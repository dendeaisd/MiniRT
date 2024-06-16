/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:37:02 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/16 16:50:53 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "object.h"

typedef struct s_camera
{
	t_vec		position;
	t_vec		orientation;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_vec		position;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_ambilight
{
	float		ratio;
	t_color		color;
}	t_ambilight;

typedef struct s_viewport
{
	float		width;
	float		height;
}	t_viewport;

typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambilight	ambilight;
	t_object	*objects; //dynamically allocated objects_nb times the t_object struct
	int			objects_nb;
	t_viewport	viewport;
}	t_scene;

// t_scene	*init_scene(void);
// void	destroy_scene(t_scene *scene);

#endif