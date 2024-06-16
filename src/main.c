/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/16 12:27:25 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_obj_data(t_object *obj)
{
	switch (obj->type)
	{
		case SPHERE:
			printf("Diameter: %f",obj->data.sphere.diameter);
			break;
		default:
			printf("Object was not initialized.\n");
	}
}

static void	ft_print_all_data(t_mini_rt *miniRT)
{
	printf("\n1.  Ambient lightning with:\n");
	printf("    - ratio: %f\n", miniRT->scene.ambilight.ratio);
	printf("    - RGB color values: %d, %d, %d\n", miniRT->scene.ambilight.color.r, miniRT->scene.ambilight.color.g, miniRT->scene.ambilight.color.b);

	printf("2.  Camera with:\n");
	printf("    - Viepoint coordinates in the form [x,y,z]: [%f,%f,%f]\n", miniRT->scene.camera.position.x, miniRT->scene.camera.position.y, miniRT->scene.camera.position.z);
	printf("    - 3d orientation vector with [x,y,z]: [%f,%f,%f]\n", miniRT->scene.camera.orientation.x, miniRT->scene.camera.orientation.y, miniRT->scene.camera.orientation.z);
	printf("    - Field of view, FOV: %f degrees\n", miniRT->scene.camera.fov);

	printf("3.  Light with:\n");
	printf("    - [x,y,z] coordinates: [%f,%f,%f]\n", miniRT->scene.light.position.x, miniRT->scene.light.position.y, miniRT->scene.light.position.z);
	printf("    - light brithness ratio: %f \n", miniRT->scene.light.brightness);
	printf("    - RGB color values: %d, %d, %d\n", miniRT->scene.light.color.r, miniRT->scene.light.color.g, miniRT->scene.light.color.b);

	printf("4. OBJECTS:\n");

	int i = -1;
	while(++i < miniRT->parser.objs_count)
	{
		if (miniRT->scene.objects[i].type == SPHERE)
		{
			printf("Object no.%d is a SPHERE with:\n", i + 1);
			printf("    - [x,y,z] coordinates of its center: [%f,%f,%f]\n", miniRT->scene.objects[i].data.sphere.center.x, miniRT->scene.objects[i].data.sphere.center.y, miniRT->scene.objects[i].data.sphere.center.z);
			printf("    - diameter: %f\n", miniRT->scene.objects[i].data.sphere.diameter);
			printf("    - RGB color values: %d, %d, %d\n", miniRT->scene.objects[i].data.sphere.color.r, miniRT->scene.objects[i].data.sphere.color.g, miniRT->scene.objects[i].data.sphere.color.b);
		}
		else if (miniRT->scene.objects[i].type == PLANE)
		{
			printf("Object no.%d is a PLANE with:\n", i + 1);
			printf("    - [x,y,z] coordinates of a point in it: [%f,%f,%f]\n", miniRT->scene.objects[i].data.plane.point.x, miniRT->scene.objects[i].data.plane.point.y, miniRT->scene.objects[i].data.plane.point.z);
			printf("    - 3d normalized normal vector with [x,y,z]: [%f,%f,%f]\n", miniRT->scene.objects[i].data.plane.normal.x, miniRT->scene.objects[i].data.plane.normal.y, miniRT->scene.objects[i].data.plane.normal.z);
			printf("    - RGB color values: %d, %d, %d\n", miniRT->scene.objects[i].data.plane.color.r, miniRT->scene.objects[i].data.plane.color.g, miniRT->scene.objects[i].data.plane.color.b);
		}
		else
		{
			printf("Object no.%d is a CYLINDER with:\n", i + 1);
			printf("    - center of [x,y,z] coordinates: [%f,%f,%f]\n", miniRT->scene.objects[i].data.cylinder.center.x, miniRT->scene.objects[i].data.cylinder.center.y, miniRT->scene.objects[i].data.cylinder.center.z);
			printf("    - 3d normalized normal vector of axis with [x,y,z]: [%f,%f,%f]\n", miniRT->scene.objects[i].data.cylinder.axis.x, miniRT->scene.objects[i].data.cylinder.axis.y, miniRT->scene.objects[i].data.cylinder.axis.z);
			printf("    - diameter: %f\n", miniRT->scene.objects[i].data.cylinder.diameter);
			printf("    - height: %f\n", miniRT->scene.objects[i].data.cylinder.height);
			printf("    - RGB color values: %d, %d, %d\n", miniRT->scene.objects[i].data.cylinder.color.r, miniRT->scene.objects[i].data.cylinder.color.g, miniRT->scene.objects[i].data.cylinder.color.b);
		}
	}
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	/* ***************** PARSING PART ***************** */
	if (argc != 2)
		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
	open_and_parse_map(argv, &mini_rt); // fd closes here

	ft_print_all_data(&mini_rt);
	
	printf("%s\n", SUCCESS);
	// printf("hello world\n");
	return (0);
	/* ************************************************* */
	
	// mini_rt = init_mini_rt(WIDTH, HEIGHT); 
	// if (!mini_rt)
	// 	return (fprintf(stderr, "Failed to init miniRT\n"), \
	// 			EXIT_FAILURE);
	// render_scene(mini_rt);
	// mlx_loop(mini_rt->window->mlx);
	// print_obj_data(mini_rt->scene->objects);
	// destroy_mini_rt(mini_rt);
	// return (EXIT_SUCCESS);
}
