/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:12 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/31 00:24:00 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <stdio.h>
# include "scene.h"
# include "ray.h"

# define WIDTH	800
# define HEIGHT	600

typedef struct s_window
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				width;
	int				height;
}	t_window;

typedef struct s_mini_rt
{
	t_window		*window;
	t_scene			*scene;
}	t_mini_rt;

t_mini_rt	*init_mini_rt(int width, int height);
void		destroy_mini_rt(t_mini_rt *mini_rt);

t_window	*init_window(int width, int height);
void		destroy_window(t_window *window);

void		render_scene(t_mini_rt *mini_rt);

#endif