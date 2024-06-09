/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/09 13:33:55 by mevangel         ###   ########.fr       */
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
	char *tmp;
	
	tmp = *line;
	while (*tmp)
	{
		if (*tmp == ',' || *tmp == '\t' || *tmp == '\n')
		// if (*tmp == ',' || *tmp == '\t')
			*tmp = ' ';
		tmp++;
	}
}

// static void	extract_elem_info(t_scene *scene, char **info, int fd)
static void	extract_elem_info(char **info)
{
	int	i;

	i = -1;
	printf("The elements of the line:\n");
	while (info[++i])
		printf("info [%d]: %s\n", i, info[i]);

	// close(fd);
	// fv_free_array(info);
}


void	parse_rt_file(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	char	**elem_info;

	(void)scene;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_exit("failed to open the file.", 1, 0);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// else if (ft_strncmp(line, "\n", 2) == 0)
		// {
		// 	free(line);
		// 	continue ;
		// }
		if (ft_strncmp(line, "\n", 2) != 0)
		{
			modify_before_split(&line);
			elem_info = ft_split(line, ' ');
			free(line);
			if (!elem_info)
				ft_error_exit("malloc for ft_split failed.", 1, fd);
			// extract_elem_info(scene, elem_info, fd);
			extract_elem_info(elem_info);
			fv_free_array(elem_info);
		}
	}
	close(fd);
}
