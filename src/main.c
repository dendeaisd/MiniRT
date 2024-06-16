/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/16 16:53:05 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_print_all_data(t_scene *scene)
{
	printf("\n1.  Ambient lightning with:\n");
	printf("    - ratio: %f\n", scene->ambilight.ratio);
	printf("    - RGB color values: %d, %d, %d\n", scene->ambilight.color.r, scene->ambilight.color.g, scene->ambilight.color.b);

	printf("2.  Camera with:\n");
	printf("    - Viepoint coordinates in the form [x,y,z]: [%f,%f,%f]\n", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
	printf("    - 3d orientation vector with [x,y,z]: [%f,%f,%f]\n", scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z);
	printf("    - Field of view, FOV: %f degrees\n", scene->camera.fov);

	printf("3.  Light with:\n");
	printf("    - [x,y,z] coordinates: [%f,%f,%f]\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("    - light brithness ratio: %f \n", scene->light.brightness);
	printf("    - RGB color values: %d, %d, %d\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);

	printf("4. OBJECTS:\n");

	int i = -1;
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

	/* ********************* PARSING PART *********************** */
	if (argc != 2)
		ft_exit("expected two arguments: ./miniRT map*.rt", 0);
	open_and_parse_map(argv, &mini_rt.scene); // fd closes here
	// to be removed later:
	ft_print_all_data(&mini_rt.scene);
	printf("%s\n", SUCCESS);
	/* ********************************************************** */
	
	return (0);
}
