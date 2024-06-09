/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/09 18:46:26 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



// static void	extract_elem_info(char **info)
// static void	extract_elem_info(t_scene *scene, char **info, int **occurences)
// {
// 	// // printing for verification:
// 	// int i = -1;
// 	// printf("The elements of the line:\n");
// 	// while (info[++i])
// 	// 	printf("info [%d]: %s\n", i, info[i]);
// 	(void)scene;

// 	int *array = *occurences;

// 	if (ft_strncmp(info[0], "A", 2) == 0)
// 		(array[0])++;
// 	else if (ft_strncmp(info[0], "C", 2) == 0)
// 		(array[1])++;
// 	else if (ft_strncmp(info[0], "L", 2) == 0)
// 		(array[2])++;
// 	else if (!ft_strncmp(info[0], "sp", 3) || !ft_strncmp(info[0], "pl", 3)
// 			|| !ft_strncmp(info[0], "cy", 3))
// 		(array[3])++;
// 	else
// 	{
// 		ft_putendl_fd(ERROR "Element can only be: A, C, L, sp, pl, or cy", 2);
// 		return ;
// 	}
// 	// init_ambient_lighting(scene->light, info);
// 	// init_camera(scene->camera, info);
// 	// close(fd);
// 	// fv_free_array(info); 
// }

// static void check_occurences(int *map)
// {
// 	int	A;
// 	int	C;
// 	int	L;
// 	int	objects_count;
	


// 	// while(*(map + 1))
// 	// {
// 	// 	if (*map == 'A' && *(map + 1) == ' ')
// 	// 		A++;
// 	// 	else if (*map == 'C' && *(map + 1) == ' ')
// 	// 		C++;
// 	// 	else if (*map == 'L' && *(map + 1) == ' ')
// 	// 		L++;
// 	// 	else if ((*map == 's' && *(map + 1) == 'p')
// 	// 		|| (*map == 'p' && *(map + 1) == 'l'))
// 	// }
// }

/*
*	Changes the line so that for example a line like:
*	L	0,0,-5 	0.4		255,255,255
*	Becomes: L	0 0 -5 0.4 255 255 255
*	So that the numbers can be properly splited after.
*/
static void modify_before_split(char **line)
{
	char *tmp;
	
	tmp = *line;
	while (*tmp)
	{
		// if (*tmp == ',' || *tmp == '\t' || *tmp == '\n')
		if (*tmp == ',' || *tmp == '\t')
			*tmp = ' ';
		tmp++;
	}
}

void	parse_map(char *map, char **map_2d)
{
	int		line;
	char	**elem_info;
	// int		i;

	map_2d = ft_split(map, '\n');
	if (!map_2d)
		ft_error_exit("malloc for split failed", 1);
	line = -1;
	while (map_2d[++line])
	{
		modify_before_split(&(map_2d[line]));
		elem_info = ft_split(map_2d[line], ' ');
		if (!elem_info)
			ft_exit_v3("malloc for split failed", 1, map_2d);
		// here i need to parse every element and init it
		// i = -1;
		// while (elem_info[++i]
		fv_free_array(elem_info);
	}
	fv_free_array(map_2d);
}

//my so_long_version
void	read_and_save_map(int fd, t_parser *parser)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || !line[0])
		ft_exit_v2("empty .rt file", 0, line, fd);
	if (ft_strlen(line) > 1000)
		ft_exit_v2("invalid map.", 0, line, fd);
	ft_strlcpy(parser->map, line, ft_strlen(line) + 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_strlcat(parser->map, line, 1024);
	}
	close(fd);
}

// void	parse_rt_file(t_scene *scene, char *file)
// {
// 	int		fd;
// 	char	*line;
// 	char	**elem_info;
// 	int		occurences[4] = {0};

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		ft_error_exit("failed to open the file.", 1, 0);
// 	while (true)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL || *line == '\0')
// 			break ;
// 		if (ft_strncmp(line, "\n", 2) != 0)
// 		{
// 			modify_before_split(&line);
// 			elem_info = ft_split(line, ' ');
// 			free(line);
// 			if (!elem_info)
// 				ft_error_exit("malloc for ft_split failed.", 1, fd);
// 			extract_elem_info(scene, elem_info, &occurences);
// 			// extract_elem_info(elem_info);
// 			fv_free_array(elem_info);
// 		}
// 	}
// 	close(fd);
// 	check_occurences(occurences);
// }
