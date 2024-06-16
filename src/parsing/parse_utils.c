/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/16 18:04:00 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Counts and returns the amount of 'lines' the (passed as parameter) 2D array has.
 */
int	ft_2darray_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Modifies the line passed as parameter, so that every comma or tab becomes space, 
 * so that after, the resulted string is splitted according to spaces. For example, 
 * the read line from the map: L	0,0,-5 	0.4		255,255,255
 * 					  becomes: L 0 0 -5  0.4  255 255 255
 * so that the numbers are properly splitted after, by one split call.
 * @param line: double pointer so that the string 'line' is passed by reference to be
 * modifiable.
 */
void	modify_before_split(char **line)
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

/**
 * @brief Checks if the string is a valid representation of a number, either integer or
 * float, rejecting strings like "0..234" or ".242" or "++123".
 * @param str: the string to be checked. Const cause it's only read here, not modified.
 * @returns TRUE: if the string is a valid representation of a number.
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

/**
 * @brief Checks for an array of strings, if each one of the strings it contains, is a
 * valid representation of a number.
 * @param array: the array of strings to be checked
 * @returns TRUE: if all the strings of the array are representing numbers.
 */
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

/**
 * @brief Exits the miniRT program, by doing the proper cleanup of two 2D arrays, one array of
 * t_object structs, and printing a relative error message to specify why it exited.
 * @param err_msg: the message that is printed to specify the error that occured
 * @param array1: the first 2D array to be freed
 * @param array2: the second 2D array to be freed
 * @param scene: pointer to access the carried 'objects' pointer, to be freed
 */
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
