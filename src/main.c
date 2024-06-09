/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/09 16:16:32 by mevangel         ###   ########.fr       */
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

void	ft_error_exit(char *err_msg, int exit_value, int fd)
{
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(err_msg, 2);
	if (fd > 2)
		close(fd);
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;
	int			fd;

	/* ***************** PARSING PART ***************** */
	if (argc != 2)
		ft_error_exit("expected two arguments in the format:\n./miniRT map.rt", 0, 0);
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_error_exit("not a .rt file", 0, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_exit("failed to open the file.", 1, 0);
	read_and_save_map(fd, &mini_rt.parser); // fd closes here
	printf("The map i read:\n%s\n", mini_rt.parser.map);
	
	// parse_map(&mini_rt.parser);
		
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