/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:12 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 20:20:24 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42/MLX42.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# include "libft.h"
# include "scene.h"
# include "ray.h"

# define WIDTH	800
# define HEIGHT	600

# define ERROR "\x1B[31mError: \x1B[0m"

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
	t_scene			scene;
}	t_mini_rt;

/* ****************************   PARSING PART   **************************** */
void	open_and_parse_map(char **argv, t_scene *scene);
void	modify_before_split(char **line);
bool	array_has_only_numbers(char **array);
int		ft_2darray_size(char **array);
bool	invalid_color(char **color_arr);

/* ********************    Initialization Functions    ********************** */
t_window	*init_window(int width, int height);
void		init_amb_light(char **info, t_scene *scene, char **map_2d);
void		init_camera(char **info, t_scene *scene, char **map_2d);
void		init_light(char **info, t_scene *scene, char **map_2d);
void		add_sphere(int obj_index, char **info, t_scene *scene, char **map_2d);
void		add_plane(int obj_index, char **info, t_scene *scene, char **map_2d);
void		add_cylinder(int obj_index, char **info, t_scene *scene, char **map_2d);

/* ***************************    General Utils    ************************** */
float	ft_atof(const char *str);

/* ******************************    Cleanup    ***************************** */
void	ft_exit(char *err_msg, int exit_value);
void	ft_exit_v2(char *msg, int exit_val, void *to_free, int fd);
void	ft_exit_v3(char *err_msg, int exit_value, char **array_to_free);
void	ft_exit_v4(char *err_msg, int exit_value, void *to_free,
			char **array_to_free);
void	ft_exit_mini_rt(char *err_msg, char **array1, char **array2,
			t_scene *scene);

#endif