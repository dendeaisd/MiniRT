/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:18:17 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/06 15:07:10 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void modify_before_split(char *line)
{
	while (*line)
	{
		if (*line == ',' || *line == '\t' || *line == '\n')
			*line = ' ';
		line++;
	}
}

static void	extract_elem_info(t_scene *scene, char **info, int fd)
{
	

	close(fd);
	fv_free_array(info);
}


void	parse_rt_file(t_scene *scene, char *file)
{
	int		fd;
	char	*line;
	char	**elem_info;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_exit("failed to open the file.", 1);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (ft_strncmp(line, "\n", 2) == 0)
		{
			free(line);
			continue ;
		}
		modify_before_split(&line);
		elem_info = ft_split(line, ' ');
		free(line);
		if (!elem_info)
		{
			close(fd);
			ft_error_exit("malloc for ft_split failed.", 1);
		}
		extract_elem_info(scene, elem_info, fd);
		fv_free_array(elem_info);
	}
	close(fd);
}
