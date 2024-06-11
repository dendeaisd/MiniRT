/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 11:46:17 by mevangel         ###   ########.fr       */
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
		// if (*tmp == ',' || *tmp == '\t' || *tmp == '\n') //i don't need it now since i'm splitting according to the '\n'
		if (*tmp == ',' || *tmp == '\t')
			*tmp = ' ';
		tmp++;
	}
}

// void allocate_objects(t_parser *parser)
// {
	
// }

static int	count_each_object(const char *map, const char *substr)
{
	const char	*tmp = map;
	int			count;
	
	count = 0;
	tmp = ft_strnstr(tmp, substr, ft_strlen(tmp));
	while (tmp != NULL)
	{
		count++;
		tmp++; // substr is "sp" or "pl" or "cy"
		tmp = ft_strnstr(tmp, substr, ft_strlen(tmp));
	}
	return (count);
}

int	find_objects_amount(const char *map)
{
	// const char	*tmp = map;
	int	count;
	
	count = 0;
	count += count_each_object(map, "sp");
	count += count_each_object(map, "pl");
	count += count_each_object(map, "cy");
	
	return count;
}

static void	parse_element(char **info, t_parser *parser)
{
	if (!ft_strncmp(info[0], "A", 2) && ft_2darray_size(info) == 5)
	{
		parser->A++;
	}
	else if (!ft_strncmp(info[0], "C", 2) && ft_2darray_size(info) == 8)
	{
		parser->C++;
	}
	else if (!ft_strncmp(info[0], "L", 2) && ft_2darray_size(info) == 8)
	{
		parser->L++;
	}
	else if (!ft_strncmp(info[0], "sp", 3) && ft_2darray_size(info) == 8)
	{
		// parser->objects_num++;
	}
	else if (!ft_strncmp(info[0], "pl", 3) && ft_2darray_size(info) == 10)
	{
		// parser->objects_num++;
	}
	else if (!ft_strncmp(info[0], "cy", 3) && ft_2darray_size(info) == 12)
	{
		// parser->objects_num++;
	}
	else
		ft_putendl_fd(ERROR "Element can only be: A, C, L, sp, pl, or cy", 2);
}

static void	parse_map(t_mini_rt *mini_rt)
{
	int		line;
	char	**map_2d;
	char	**elem_info;
	// int		i;

	// check_characters();
	// (void)parser;
	// printf("\nCount of objects is: %d\n", find_objects_amount(map));
	
	mini_rt->scene.objects = (t_object *)malloc(find_objects_amount(mini_rt->parser.map) * sizeof(t_object));
	map_2d = ft_split(mini_rt->parser.map, '\n'); // First split for the 1D map to split it to its lines
	if (map_2d == NULL)
		ft_error_exit("malloc for split failed", 1);
	line = -1;
	while (map_2d[++line])
	{
		// printf("%s\n", map_2d[line]);
		modify_before_split(&(map_2d[line]));
		elem_info = ft_split(map_2d[line], ' '); //second split to divide the numbers/info of each element(in each line)
		// printf("object is %s and size is %d\n", elem_info[0], ft_2darray_size(elem_info));
		if (!elem_info)
			ft_exit_v3("malloc for split failed", 1, map_2d);
		parse_element(elem_info, &mini_rt->parser);
		// here i need to parse every element and init it
		// i = -1;
		// while (elem_info[++i]
		fv_free_array(elem_info);
	}
	fv_free_array(map_2d);
}


//my so_long_version
void	read_and_save_map(int fd, t_mini_rt *mini_rt)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || !line[0])
		ft_exit_v2("empty .rt file", 0, line, fd);
	if (ft_strlen(line) > 1000)
		ft_exit_v2("invalid map.", 0, line, fd);
	ft_strlcpy(mini_rt->parser.map, line, ft_strlen(line) + 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_strlcat(mini_rt->parser.map, line, 1024);
	}
	close(fd);
	parse_map(mini_rt);
}


// // the first first version of reading the file. Worked but unpractical for after.
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