/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:12 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/22 05:05:49 by fvoicu           ###   ########.fr       */
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
# include <pthread.h>

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
	t_window		window;
	t_scene			scene;
}	t_mini_rt;

typedef struct s_thread_data
{
	t_mini_rt		*mini_rt;
	int				th_idx;
	int				th_nb;
}	t_thread_data;

/* ****************************   PARSING PART   **************************** */
void	open_and_parse_map(char **argv, t_scene *scene);
void	modify_before_split(char **line);
bool	array_has_only_numbers(char **array);
int		ft_2darray_size(char **array);
bool	invalid_color(char **color_arr);

/* ********************    Initialization Functions    ********************** */
void		init_window(t_mini_rt *mini_rt, int width, int height);
void		init_amb_light(char **info, t_scene *scene, char **map_2d);
void		init_camera(char **info, t_scene *scene, char **map_2d);
void		init_light(char **info, t_scene *scene, char **map_2d);
void		add_sphere(int obj_index, char **info, t_scene *scene, char **map_2d);
void		add_plane(int obj_index, char **info, t_scene *scene, char **map_2d);
void		add_cylinder(int obj_index, char **info, t_scene *scene, char **map_2d);

// From FLAVIA. We need name for the category here... *********************** *

void			setup_camera(t_camera *camera, int width, int height);
t_ray			generate_ray(t_scene *scene, t_window *window, int x, int y);
unsigned int	get_pixel_color(int obj_idx, t_scene *scene, \
						t_ray ray, float distance);
void			render_scene(t_mini_rt *mini_rt);


/**Light**/
unsigned int	vec_to_color(t_color color);
t_color			cast_light(t_scene *scene, t_color obj_color, \
						t_vec hit_point, t_vec normal);
bool			cast_shadow(t_scene *scene, t_vec hit_point, \
						t_light light, t_vec normal);

/* ***************************    General Utils    ************************** */
float	ft_atof(const char *str);

/* ******************************    Cleanup    ***************************** */
void	cleanup_before_exit(t_mini_rt *mini_rt);

void	ft_exit(char *err_msg, int exit_value);
void	ft_exit_v2(char *msg, int exit_val, void *to_free, int fd);
void	ft_exit_v3(char *err_msg, int exit_value, char **array_to_free);
void	ft_exit_v4(char *err_msg, int exit_value, void *to_free,
			char **array_to_free);
void	ft_exit_mini_rt(char *err_msg, char **array1, char **array2,
			t_scene *scene);

#endif