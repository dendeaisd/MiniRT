/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 11:38:17 by mevangel         ###   ########.fr       */
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
	int			fd; 

	/* ***************** PARSING PART ***************** */
	if (argc != 2)
		ft_error_exit("expected two arguments in the format:\n./miniRT map.rt", 0);
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_error_exit("not a .rt file", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_exit("failed to open the file.", 1);
	read_and_save_map(fd, &mini_rt); // fd closes here
	// printf("The map i read:\n%s\n", mini_rt.parser.map);
	// parse_map(mini_rt.parser.map, &mini_rt.parser.map_2d);
	
	
	// // To check the saving of the 2d map in the struct:
	// int i = -1;
	// while (mini_rt.parser.map_2d[++i])
	// 	printf("line [%d]: %s\n", i, mini_rt.parser.map_2d[i]);
	
		
	// parse_rt_file(&mini_rt.scene, argv[1]);

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