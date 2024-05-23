/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/24 01:40:26 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

#include <stdio.h>

int main() {
    // t_vec v1 = {1.0, 2.0, 3.0};
    // t_vec v2 = {4.0, 5.0, 6.0};
    // float scalar = 2.f;
    
    // t_vec add = vec_add(v1, v2);
		// t_vec sub = vec_sub(v1, v2);
    // t_vec mul = vec_mul(v1, scalar);
    // t_vec div = vec_div(v2, scalar);
    // float dot_product = vec_dot(v1, v2);
    // t_vec cross_product = vec_cross(v1, v2);
    // t_vec unit_vector = vec_unit(v1);
    
    
		// printf("v1 = 		(%f, %f, %f)\n", v1.x, v1.y, v1.z);
		// printf("v2 = 		(%f, %f, %f)\n\n", v2.x, v2.y, v2.z);
    // printf("Addition:	(%f, %f, %f)\n", add.x, add.y, add.z);
		// printf("Substraction:	(%f, %f, %f)\n", sub.x, sub.y, sub.z);
		// printf("Multiplication:	(%f, %f, %f)\n", mul.x, mul.y, mul.z);
		// printf("Division:	(%f, %f, %f)\n", div.x, div.y, div.z);
    // printf("Dot Product: %f\n", dot_product);
    // printf("Cross Product: (%f, %f, %f)\n", cross_product.x, cross_product.y, cross_product.z);
    // printf("Unit Vector: (%f, %f, %f)\n", unit_vector.x, unit_vector.y, unit_vector.z);

    t_vec origin = {0.0f, 0.0f, 0.0f};
    t_vec direction = {1.0f, 2.0f, 3.0f};
    t_ray ray = generate_ray(origin, direction);
    
    float t = 2.0f;
    t_vec point = ray_at(ray, t);
    
    printf("Ray at t = %.2f : (%.2f, %.2f, %.2f)\n", t, point.x, point.y, point.z);
    return 0;
}
