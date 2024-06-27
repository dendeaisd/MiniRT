/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/27 03:26:44 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Counts the occurence of the 'substr' string in the 'map' string.
 * @param map: the string where to check.
 * @param substr: the string whose occurences are looked inside 'map'.
 * @returns The number it counted.
 */
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

/**
 * @brief Counts the occurences of the strings "sp", "pl" and "cy" (the
 * "objects" of the scene)to save the number of objects in total, and 
 * checks if the strings "A", "C" and "L" occur only one time in the map,
 * since Ambient lightning (A), Camera (C) and Light(L) must be declared once.
 * @param scene: passed in order to modify the objects_nb that it carries
 * @param map_1d: the firstly read 1D map, allocated on the stack.
 */
static void	count_elements(t_scene *scene, char *map_1d)
{
	int	count;
	int	a;
	int	c;
	int	l;

	count = 0;
	count += count_each_object(map_1d, "sp");
	count += count_each_object(map_1d, "pl");
	count += count_each_object(map_1d, "cy");
	count += count_each_object(map_1d, "cn");
	scene->objects_nb = count;
	a = count_each_object(map_1d, "A");
	c = count_each_object(map_1d, "C");
	l = count_each_object(map_1d, "L");
	if (a != 1 || c != 1 || l != 1)
		ft_exit("Ambient lightning (A), Camera (C) and Light(L) must be "
			"declared once.", 0);
}

/**
 * @brief It parses every line (char **info) of the map, checking the first
 * string every time which is the identifier of the element, and according to
 * that it initializes the corresponding element or object. (For the objects 
 * it uses the static variable so that the object is properly placed in the 
 * dynamically allocated array of objects pointed to by "scene->objects".) It
 * also checks for the proper amount of arguments/information for every 
 * element/object. If the number is not the correct or the identifier is 
 * none of the expected 6, it exits.
 * @param info: the 2d array of strings that the current line of the map has.
 * @param scene: the struct that contains the variables to store the read data.
 * @param map2: the 2d array of the rt map file, to be freed in case of exit.
 */
static void	parse_element(char **info, t_scene *scene, char **map2)
{
	static int	obj_cur_index = -1;

	if (!ft_strncmp(info[0], "A", 2) && ft_2darray_size(info) == 5)
		init_amb_light(info, scene, map2);
	else if (!ft_strncmp(info[0], "C", 2) && ft_2darray_size(info) == 8)
		init_camera(info, scene, map2);
	else if (!ft_strncmp(info[0], "L", 2) && (ft_2darray_size(info) == 5
			|| ft_2darray_size(info) == 8))
		init_light(info, scene, map2);
	else if (!ft_strncmp(info[0], "sp", 3) && ft_2darray_size(info) == 8)
		add_sphere(++obj_cur_index, info, scene, map2);
	else if (!ft_strncmp(info[0], "pl", 3) && ft_2darray_size(info) == 10)
		add_plane(++obj_cur_index, info, scene, map2);
	else if (!ft_strncmp(info[0], "cy", 3) && ft_2darray_size(info) == 12)
		add_cylinder(++obj_cur_index, info, scene, map2);
	else if (!ft_strncmp(info[0], "cn", 3) && ft_2darray_size(info) == 12)
		add_cone(++obj_cur_index, info, scene, map2);
	else
		ft_exit_mini_rt("invalid rt map.", info, map2, scene);
}

/**
 * @brief It counts how many elements/objects there are counting the strings
 * "A", "C", "L", "sp", "pl", "cy" in the map_1d, and then allocates 
 * accordingly number of objects times the t_object struct. It parses the map
 * one line at a time, and then splits each line to its content, to store the
 * corresponding values/characteristics of each element/object.
 * @param scene: the struct that carries all the necessary variables to modify.
 * @param map_1d: the readen from the fd map, saved as one string.
 */
static void	parse_map(t_scene *scene, char *map_1d)
{
	int		line;
	char	**elem_info;
	char	**map2;

	count_elements(scene, map_1d);
	scene->objects = (t_object *)malloc((scene->objects_nb) * sizeof(t_object));
	if (scene->objects == NULL)
		ft_exit("malloc for objects failed", 1);
	map2 = ft_split(map_1d, '\n');
	if (map2 == NULL)
		ft_exit_v2("malloc for split failed", 1, scene->objects, -1);
	line = -1;
	while (map2[++line])
	{
		modify_before_split(&(map2[line]));
		elem_info = ft_split(map2[line], ' ');
		if (!elem_info)
			ft_exit_v4("malloc for split failed", 1, scene->objects, map2);
		parse_element(elem_info, scene, map2);
		fv_free_array(elem_info);
	}
	fv_free_array(map2);
}

/**
 * @brief Opens the file of the map, passed as 2nd argument (argv[1]), and saves
 * its content on the stack (char map[1024] in the parser struct), ignoring 
 * the commented lines (starting with '#') and checking for empty files, wrong 
 * file extension or invalid size. It closes the corresponding fd at the end, 
 * and sends the readen for parsing.
 * @param argv: it carries the relative path to the .rt file as argv[1]
 * @param scene: the struct that carries the variables for the map to be used.
 */
void	open_and_parse_map(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;
	char	map[4096];

	if (ft_strncmp((argv[1] + (ft_strlen(argv[1]) - 3)), ".rt", 4) != 0)
		ft_exit("not a .rt file", 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("failed to open the file", 1);
	line = get_next_line(fd);
	if (!line || !line[0] || ft_strlen(line) > 4096)
		ft_exit_v2("invalid .rt file", 0, line, fd);
	if (line[0] != '#')
		ft_strlcpy(map, line, ft_strlen(line) + 1);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] != '#')
			ft_strlcat(map, line, 4096);
	}
	close(fd);
	parse_map(scene, map);
}
