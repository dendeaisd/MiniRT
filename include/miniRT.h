/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:12 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/30 21:43:39 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <MLX42/MLX42.h>
# include "scene.h"

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				width;
	int				height;
}	t_window;

typedef struct s_miniRT
{
	t_window		*window;
	t_scene			*scene;
}	t_miniRT;

#endif