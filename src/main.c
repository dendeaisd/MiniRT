/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 02:39:38 by mevangel         ###   ########.fr       */
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

void	ft_print_all_data(t_scene *scene)
{
	printf("\n1.  Ambient lightning with:\n");
	printf("    - ratio: %f\n", scene->ambilight.ratio);
	printf("    - RGB color values: %d, %d, %d\n", scene->ambilight.color.r, scene->ambilight.color.g, scene->ambilight.color.b);

	printf("2.  Camera with:\n");
	printf("    - Viepoint coordinates in the form [x,y,z]: [%f,%f,%f]\n", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
	printf("    - 3d orientation vector with [x,y,z]: [%f,%f,%f]\n", scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z);
	printf("    - Field of view, FOV: %f degrees\n", scene->camera.fov);

	printf("3.  Light with:\n");
	printf("    - [x,y,z] coordinates: [%f,%f,%f]\n", scene->lights[0].position.x, scene->lights[0].position.y, scene->lights[0].position.z);
	printf("    - lights[0] brithness ratio: %f \n", scene->lights[0].brightness);
	printf("    - RGB color values: %d, %d, %d\n", scene->lights[0].color.r, scene->lights[0].color.g, scene->lights[0].color.b);

	
	printf("3b.  Additional Bonus Lights with:\n");
	int i = 0;
	while(++i < scene->lights_nb)
	{
		printf("    Light no.%d:\n", i + 1);
		printf("    - [x,y,z] coordinates: [%f,%f,%f]\n", scene->lights[i].position.x, scene->lights[i].position.y, scene->lights[i].position.z);
		printf("    - lights[i] brithness ratio: %f \n", scene->lights[i].brightness);
		printf("    - RGB color values: %d, %d, %d\n", scene->lights[i].color.r, scene->lights[i].color.g, scene->lights[i].color.b);
	}

	printf("4. OBJECTS:\n");
	i = -1;
	while(++i < scene->objects_nb)
	{
		if (scene->objects[i].type == SPHERE)
		{
			printf("Object no.%d is a SPHERE with:\n", i + 1);
			printf("    - [x,y,z] coordinates of its center: [%f,%f,%f]\n", scene->objects[i].data.sphere.center.x, scene->objects[i].data.sphere.center.y, scene->objects[i].data.sphere.center.z);
			printf("    - diameter: %f\n", scene->objects[i].data.sphere.diameter);
			printf("    - RGB color values: %d, %d, %d\n", scene->objects[i].data.sphere.color.r, scene->objects[i].data.sphere.color.g, scene->objects[i].data.sphere.color.b);
		}
		else if (scene->objects[i].type == PLANE)
		{
			printf("Object no.%d is a PLANE with:\n", i + 1);
			printf("    - [x,y,z] coordinates of a point in it: [%f,%f,%f]\n", scene->objects[i].data.plane.point.x, scene->objects[i].data.plane.point.y, scene->objects[i].data.plane.point.z);
			printf("    - 3d normalized normal vector with [x,y,z]: [%f,%f,%f]\n", scene->objects[i].data.plane.normal.x, scene->objects[i].data.plane.normal.y, scene->objects[i].data.plane.normal.z);
			printf("    - RGB color values: %d, %d, %d\n", scene->objects[i].data.plane.color.r, scene->objects[i].data.plane.color.g, scene->objects[i].data.plane.color.b);
		}
		else
		{
			printf("Object no.%d is a CYLINDER with:\n", i + 1);
			printf("    - center of [x,y,z] coordinates: [%f,%f,%f]\n", scene->objects[i].data.cylinder.center.x, scene->objects[i].data.cylinder.center.y, scene->objects[i].data.cylinder.center.z);
			printf("    - 3d normalized normal vector of axis with [x,y,z]: [%f,%f,%f]\n", scene->objects[i].data.cylinder.axis.x, scene->objects[i].data.cylinder.axis.y, scene->objects[i].data.cylinder.axis.z);
			printf("    - diameter: %f\n", scene->objects[i].data.cylinder.diameter);
			printf("    - height: %f\n", scene->objects[i].data.cylinder.height);
			printf("    - RGB color values: %d, %d, %d\n", scene->objects[i].data.cylinder.color.r, scene->objects[i].data.cylinder.color.g, scene->objects[i].data.cylinder.color.b);
		}
	}
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	atexit(check_leaks); //! to be removed later
	if (argc != 2)
		ft_exit("expected two arguments in the format:"
			" ./miniRT map.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene);
	ft_print_all_data(&mini_rt.scene);
	//from now on, the only thing from parsin that needs to be freed is the 'mini_rt->scene->objects' pointer
	init_window(&mini_rt, WIDTH, HEIGHT);
	// print_obj_data(mini_rt.scene.objects);
	render_scene(&mini_rt);
	mlx_loop(mini_rt.window.mlx);
	cleanup_and_exit(1, NULL, &mini_rt);
	return (0);
}

