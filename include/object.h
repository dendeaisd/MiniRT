/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:54:16 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 20:57:59 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "vec3.h"
# include "ray.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	t_vec	center;
	float	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	axis;
	float	diameter;
	float	height;
	t_color	color;
}	t_cylinder;

typedef union u_obj_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_obj_data;

typedef struct s_object
{
	t_obj_type	type;
	t_obj_data	data;
}	t_object;

/***INTERSECTION***/
//*SPHERE*//
float	calculate_discriminant(t_ray *ray, t_sphere *sphere, \
							float *b, float *c);
bool	solve_quadratic(float b, float discriminant, float *t0, float *t1);
bool	find_closest_hit(float t0, float t1, float *t);
bool	intersect_sphere(t_ray * ray, t_sphere * sphere, float *t);

//*PLANE*//
bool    intersect_plane(t_ray *ray, t_plane *plane, float *t);

// *CYLINDER*//
bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *t);

#endif