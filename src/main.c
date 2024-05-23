/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/23 22:18:53 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdio.h>

int main() {
    t_vec v1 = {1.0, 2.0, 3.0};
    t_vec v2 = {4.0, 5.0, 6.0};
    t_vec add = vec_add(v1, v2);
		t_vec sub = vec_sub(v1, v2);
    
		printf("v1 = 		(%f, %f, %f)\n", v1.x, v1.y, v1.z);
		printf("v2 = 		(%f, %f, %f)\n\n", v2.x, v2.y, v2.z);
    printf("Addition:	(%f, %f, %f)\n", add.x, add.y, add.z);
		printf("Substraction:	(%f, %f, %f)\n", sub.x, sub.y, sub.z);
    return 0;
}
