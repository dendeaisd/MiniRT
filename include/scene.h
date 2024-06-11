/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:37:02 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 13:16:17 by mevangel         ###   ########.fr       */
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
}	t_light;

typedef struct s_ambilight
{
	float		ratio;
	t_vec		color;
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
	t_object	*objects; //dynamically allocated number_of_objects times the t_object struct
	int			objects_nb; //Flavia is using that equal to 1
	int			objs_count;
	t_viewport	viewport;
}	t_scene;

t_scene	*init_scene(void);
void	destroy_scene(t_scene *scene);

#endif