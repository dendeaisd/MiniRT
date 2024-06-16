/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/16 16:38:39 by mevangel         ###   ########.fr       */
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
		tmp++;
		tmp = ft_strnstr(tmp, substr, ft_strlen(tmp));
	}
	return (count);
}

static void	count_elements(t_scene *scene, char *map_1d)
{
	int	count;
	int	A;
	int	C;
	int	L;

	count = 0;
	count += count_each_object(map_1d, "sp");
	count += count_each_object(map_1d, "pl");
	count += count_each_object(map_1d, "cy");
	scene->objects_nb = count;
	A = count_each_object(map_1d, "A");
	C = count_each_object(map_1d, "C");
	L = count_each_object(map_1d, "L");
	if (A != 1 || C != 1 || L != 1)
		ft_exit("Ambient lightning (A), Camera (C) and Light(L) must be declared once.", 0);
}


static void	parse_element(char **info, t_scene *scene, char **map_2d)
{
	static int obj_cur_index = -1;
	
	if (!ft_strncmp(info[0], "A", 2) && ft_2darray_size(info) == 5)
		init_amb_light(info, scene, map_2d);
	else if (!ft_strncmp(info[0], "C", 2) && ft_2darray_size(info) == 8)
		init_camera(info, scene, map_2d);
	else if (!ft_strncmp(info[0], "L", 2) && (ft_2darray_size(info) == 5 || ft_2darray_size(info) == 8)) //5 in mandatory, 8 in bonus
		init_light(info, scene, map_2d);
	else if (!ft_strncmp(info[0], "sp", 3) && ft_2darray_size(info) == 8)
		add_sphere(++obj_cur_index, info, scene, map_2d);
	else if (!ft_strncmp(info[0], "pl", 3) && ft_2darray_size(info) == 10)
		add_plane(++obj_cur_index, info, scene, map_2d);
	else if (!ft_strncmp(info[0], "cy", 3) && ft_2darray_size(info) == 12)
		add_cylinder(++obj_cur_index, info, scene, map_2d);
	else
		ft_exit_miniRT("invalid rt map.", info, map_2d, scene);
}

static void	parse_map(t_scene *scene, char *map_1d)
{
	int		line;
	char	**elem_info;
	char	**map_2d;

	count_elements(scene, map_1d);
	scene->objects = (t_object *)malloc((scene->objects_nb) * sizeof(t_object));
	if (scene->objects == NULL)
		ft_exit("malloc for objects failed", 1);
	map_2d = ft_split(map_1d, '\n'); // First split for the 1D map to split it to its lines
	if (map_2d == NULL)
		ft_exit_v2("malloc for split failed", 1, scene->objects, -1);
	line = -1;
	while (map_2d[++line])
	{
		modify_before_split(&(map_2d[line]));
		elem_info = ft_split(map_2d[line], ' '); //second split to divide the numbers/info of each element(in each line)
		if (!elem_info)
			ft_exit_v4("malloc for split failed", 1, scene->objects, map_2d);
		parse_element(elem_info, scene, map_2d);
		fv_free_array(elem_info);
	}
	fv_free_array(map_2d);
}


/**
 * @brief Opens the file of the map, passed as 2nd argument, and saves its content on the
 * stack (char map[1024], parser struct), ignoring the commented lines (starting with '#')
 * and checking for empty files, wrong file extension or invalid size. It closes the 
 * corresponding fd at the end, and sends the readen for parsing.
 * @param argv: it carries the relative path to the .rt file as argv[1]
 * @param scene: the struct that carries the variables for the map to be used.
 */
void	open_and_parse_map(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;
	char	map[1024];

	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_exit("not a .rt file", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("failed to open the file", 1);
	line = get_next_line(fd);
	if (!line || !line[0] || ft_strlen(line) > 1024)
		ft_exit_v2("invalid .rt file", 0, line, fd);
	ft_strlcpy(map, line, ft_strlen(line) + 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '#')
			ft_strlcat(map, line, 1024);
	}
	close(fd);
	parse_map(scene, map);
}
