/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 02:37:02 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/23 06:45:04 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "object.h"

# define SPOTLIGHT_DIRECTION (t_vec){0.0f, 0.0f, 0.0f} // Default direction towards center
// # define SPOTLIGHT_CUTOFF_ANGLE cos(M_PI / 6) // 30 degrees
// # define SPOTLIGHT_OUTER_CUTOFF_ANGLE cos(M_PI / 4) // 45 degrees

# define SPOTLIGHT_CUTOFF_ANGLE cos(M_PI / 12) //15
# define SPOTLIGHT_OUTER_CUTOFF_ANGLE cos(M_PI / 9) // 20 degrees

// # define SPOTLIGHT_CUTOFF_ANGLE cos(M_PI / 4) //45
// # define SPOTLIGHT_OUTER_CUTOFF_ANGLE cos(M_PI / 3) //60


typedef struct s_viewport
{
	float		width;
	float		height;
}	t_viewport;

typedef struct s_camera
{
	t_vec		position;
	t_vec		orientation;
	float		fov;
	float		ratio;		//! addition from Flavia
	t_viewport	viewport;	//! addition from Flavia
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

typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambilight	ambilight;
	t_object	*objects;
	int			objects_nb;
	t_viewport	viewport;
}	t_scene;

#endif