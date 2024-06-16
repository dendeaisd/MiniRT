/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/16 16:39:09 by mevangel         ###   ########.fr       */
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

/*
*	returns true in strings like: 1,  2.0405 235
*	returns false in strings like:
*	0..2452
*	.352
*	++141
*/
static bool	ft_str_is_number(const char *str)
{
	bool found_dot;
	
	if (!str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit((int)*str))
		return (false);
	found_dot = false;
	while (*(++str))
	{
		if (found_dot == true && *str == '.')
			return (false);
		if (*str == '.')
			found_dot = true;
		else if (!ft_isdigit((int)*str))
			return (false);
	}
	return (true);
}

bool	array_has_only_numbers(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (ft_str_is_number(array[i]) == false)
			return (false);
	}
	return (true);
}

void	ft_exit_miniRT(char *err_msg, char **array1, char **array2, t_scene *scene)
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
	exit(EXIT_SUCCESS);
}
