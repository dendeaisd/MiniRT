/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/23 01:50:24 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void check_leaks(void)
{
	system("leaks miniRT");
}

void print_obj_data(t_object *obj)
{
	switch (obj->type)
	{
		case SPHERE:
			printf("center: %f,", obj->data.sphere.center.x);
			printf("%f,", obj->data.sphere.center.y);
			printf("%f\n", obj->data.sphere.center.z);
			printf("center: %f,", obj->data.sphere.center.x);
			printf("%f,", obj->data.sphere.center.y);
			printf("%f\n", obj->data.sphere.center.z);
			printf("Diameter: %f",obj->data.sphere.diameter);
			break;
		default:
			printf("Object was not initialized.\n");
	}
}

// int	main(int argc, char **argv)
// {
// 	t_mini_rt	mini_rt;

// 	// atexit(check_leaks); //! to be removed later
// 	if (argc != 2)
// 		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
// 	open_and_parse_map(argv, &mini_rt.scene);
// 	//from now on, the only thing from parsin that need to be freed is the 'mini_rt->scene->objects' pointer
// 	init_window(&mini_rt, WIDTH, HEIGHT);
// 	// print_obj_data(mini_rt.scene.objects);
// 	render_scene(&mini_rt);
// 	mlx_loop(mini_rt.window.mlx);
// 	cleanup_before_exit(&mini_rt);
// 	return (EXIT_SUCCESS);
// }

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <cpuid.h>
#endif

int main(void)
{
// 	int info[4];
// #if defined(_MSC_VER)
// 	__cpuid(info, 1);
// #else
// 	__cpuid(1, info[0], info[1], info[2], info[3]);
// #endif

// 	if (info[2] & ((int)1 << 28))
// 		printf("AVX is supported!\n");
// 	else
// 		printf("AVX is not supported.\n");
// 	return 0;
    t_vec a = {1.0f, 2.0f, 3.0f};
    t_vec b = {4.0f, 5.0f, 6.0f};
    t_vec result = vec_sub(a, b);

    printf("Result of vec_add:\n");
    printf("x: %f\n", result.x);
    printf("y: %f\n", result.y);
    printf("z: %f\n", result.z);

    return 0;
}
