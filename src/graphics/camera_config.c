/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:56:06 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/25 11:18:56 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	calc_aspect_ratio(int width, int height)
{
	return ((float)width / (float)height);
}

static void	calc_viewport_dim(t_camera *camera, float aspect_ratio, \
						t_viewport *viewport)
{
	viewport->height = 2.f * tanf(camera->fov * M_PI / 360.f);
	viewport->width = viewport->height * aspect_ratio;
}

void	setup_camera(t_camera *camera, int width, int height)
{
	camera->ratio = calc_aspect_ratio(width, height);
	calc_viewport_dim(camera, camera->ratio, \
						&camera->viewport);
}
