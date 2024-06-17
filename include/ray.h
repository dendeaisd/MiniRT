/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:56:30 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/17 15:18:25 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vec3.h"

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

#endif