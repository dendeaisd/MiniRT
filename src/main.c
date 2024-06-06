/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/06 15:02:27 by mevangel         ###   ########.fr       */
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

void	ft_error_exit(char *err_msg, int exit_value)
{
	ft_putstr_fd("\033[31mError:\033[37m ", 2);
	ft_putendl_fd(err_msg, 2);
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_mini_rt	mini_rt;

	/* ***************** PARSING PART ***************** */
	if (argc != 2)
		ft_error_exit("expected two arguments: ./miniRT *.rt", 0);
	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_error_exit("not a .rt file", 0);
	parse_rt_file(&mini_rt.scene, argv[1]);

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