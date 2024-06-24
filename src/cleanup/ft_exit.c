/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:57 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/24 01:59:29 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_exit(char *err_msg, int exit_value)
{
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(err_msg, 2);
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_exit_v2(char *msg, int exit_val, void *to_free, int fd)
{
	ft_putstr_fd("\033[31mError:\033[37m ", 2);
	ft_putendl_fd(msg, 2);
	if (to_free)
		free(to_free);
	if (fd > 2)
		close(fd);
	if (exit_val == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_exit_v3(char *err_msg, int exit_value, char **array_to_free)
{
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(err_msg, 2);
	if (array_to_free)
		fv_free_array(array_to_free);
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_exit_v4(char *err_msg, int exit_value, void *to_free,
	char **array_to_free)
{
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(err_msg, 2);
	if (to_free)
		free(to_free);
	if (array_to_free)
		fv_free_array(array_to_free);
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

/**
 * @brief Exits the miniRT program, by doing the proper cleanup of two 2D
 * arrays, one array of t_object structs, and printing a relative error 
 * message to specify why it exited.
 * @param err_msg: the message that is printed to specify the error occured
 * @param array1: the first 2D array to be freed
 * @param array2: the second 2D array to be freed
 * @param scene: pointer to access the carried 'objects' pointer, to be freed
 */
void	ft_exit_mini_rt(char *err_msg, char **array1, char **array2,
	t_scene *scene)
{
	if (err_msg)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putendl_fd(err_msg, 2);
	}
	if (array1)
		fv_free_array(array1);
	if (array2)
		fv_free_array(array2);
	if (scene->objects)
		free(scene->objects);
	if (scene->lights)
		free(scene->lights);
	exit(EXIT_SUCCESS);
}
