/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 14:04:44 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
*	Changes the line so that for example a line like:
*	L	0,0,-5 	0.4		255,255,255
*	Becomes: L	0 0 -5 0.4 255 255 255
*	So that the numbers can be properly splited after.
*/
static void modify_before_split(char **line)
{
	char	*tmp;
	
	tmp = *line;
	while (*tmp)
	{
		if (*tmp == ',' || *tmp == '\t')
			*tmp = ' ';
		tmp++;
	}
}

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

static void	count_elements(t_parser *parser)
{
	// const char	*tmp = map;
	int		count;
	int		A;
	int		C;
	int		L;
	
	count = 0;
	count += count_each_object(parser->map, "sp");
	count += count_each_object(parser->map, "pl");
	count += count_each_object(parser->map, "cy");
	parser->objs_count = count;
	A = count_each_object(parser->map, "A ");
	C = count_each_object(parser->map, "C ");
	L = count_each_object(parser->map, "L ");
	if (A != 1 || C != 1 || L != 1)
		ft_exit("Ambient lightning (A), Camera (C) and Light(L) must be declared once.", 0);
}

static void	parse_element(char **map_2d, char **info, t_mini_rt *mini_rt)
{
	static int obj_cur_index = 0;
	
	if (!ft_strncmp(info[0], "A", 2) && ft_2darray_size(info) == 5)
		init_amb_light(map_2d, info, mini_rt);
	else if (!ft_strncmp(info[0], "C", 2) && ft_2darray_size(info) == 8)
	{
		// parser->C++;
	}
	else if (!ft_strncmp(info[0], "L", 2) && ft_2darray_size(info) == 8)
	{
		// parser->L++;
	}
	else if (!ft_strncmp(info[0], "sp", 3) && ft_2darray_size(info) == 8)
	{
		obj_cur_index++;
	}
	else if (!ft_strncmp(info[0], "pl", 3) && ft_2darray_size(info) == 10)
	{
		obj_cur_index++;
	}
	else if (!ft_strncmp(info[0], "cy", 3) && ft_2darray_size(info) == 12)
	{
		obj_cur_index++;
	}
	else
	{
		fv_free_array(info);
		ft_exit_v4("Element can only be one of the following: A, C, L, sp, pl, or cy", 0, mini_rt->scene.objects, map_2d);
	}
}

static void	parse_map(t_mini_rt *mini_rt)
{
	int		line;
	char	**map_2d;
	char	**elem_info;
	// int		i;

	count_elements(&mini_rt->parser);
	printf("\nCount of objects is: %d\n", mini_rt->parser.objs_count);
	// mini_rt->scene.objects = (t_object *)ft_calloc((mini_rt->parser.objs_count + 1), sizeof(t_object));
	mini_rt->scene.objects = (t_object *)malloc((mini_rt->parser.objs_count) * sizeof(t_object));
	if (mini_rt->scene.objects == NULL)
		ft_exit("malloc for objects failed", 1);
	
	map_2d = ft_split(mini_rt->parser.map, '\n'); // First split for the 1D map to split it to its lines
	if (map_2d == NULL)
		ft_exit_v2("malloc for split failed", 1, mini_rt->scene.objects, -1);

	line = -1;
	while (map_2d[++line])
	{
		modify_before_split(&(map_2d[line]));
		elem_info = ft_split(map_2d[line], ' '); //second split to divide the numbers/info of each element(in each line)
		if (!elem_info)
			ft_exit_v4("malloc for split failed", 1, mini_rt->scene.objects, map_2d);
		parse_element(map_2d, elem_info, mini_rt);
		fv_free_array(elem_info);
	}
	fv_free_array(map_2d);
}

//my so_long_version
void	open_and_parse_map(char **argv, t_mini_rt *mini_rt)
{
	int		fd; 
	char	*line;

	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_exit("not a .rt file", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("failed to open the file.", 1);
	line = get_next_line(fd);
	if (!line || !line[0])
		ft_exit_v2("empty .rt file", 0, line, fd);
	if (ft_strlen(line) > 1024)
		ft_exit_v2("invalid map.", 0, line, fd);
	ft_strlcpy(mini_rt->parser.map, line, ft_strlen(line) + 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '#')
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