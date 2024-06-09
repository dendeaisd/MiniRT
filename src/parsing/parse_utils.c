/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/09 17:21:06 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_2darray_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return(i);
}

void	ft_exit_v2(char *msg, int exit_val, void *to_free, int fd)
{
	ft_putstr_fd("\033[31mError:\033[37m ", 2);
	ft_putendl_fd(msg, 2);
	free(to_free);
	close(fd);
	if (exit_val == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

void	ft_error_exit(char *err_msg, int exit_value)
{
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(err_msg, 2);
	if (exit_value == 1)
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
