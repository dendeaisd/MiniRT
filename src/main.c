/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 17:21:55 by mevangel         ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	/* ***************** PARSING PART ***************** */
	if (argc != 2)
		ft_exit("expected two arguments in the format:\n./miniRT map.rt", 0);
	open_and_parse_map(argv, &mini_rt); // fd closes here
	// printf("The map i read:\n%s\n", mini_rt.parser.map);
	// parse_map(mini_rt.parser.map, &mini_rt.parser.map_2d);
	
	//in order to check if the ambilight values passed correctly:
	// printf("For ambilight, currently save:")
	printf("%s\n", SUCCESS);
	return 0;
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