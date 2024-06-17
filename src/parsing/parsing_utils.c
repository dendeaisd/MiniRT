/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/17 15:47:34 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Counts and returns the amount of 'lines' the 2D array has.
 * @param array: the 2D array to be checked
 * @returns: the number of strings this array contains
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
 * @brief Modifies the line passed as parameter, so that every comma or tab
 * becomes space, so that after, the resulted string is splitted according 
 * to spaces. For example, the read line from the map:
 * 			L	0,0,-5 	0.4		255,255,255
 * becomes: L 0 0 -5  0.4  255 255 255
 * so that the numbers are properly splitted after, by one split call.
 * @param line: double pointer so that the string 'line' is passed by 
 * reference to be modifiable.
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
 * @brief Checks if the string is a valid representation of a number, either
 * integer or float, rejecting strings like "0..234" or ".242" or "++123".
 * @param str: the string to be checked. Const cause it's not modified here.
 * @returns TRUE: if the string is a valid representation of a number.
 */
static bool	ft_str_is_number(const char *str)
{
	bool	found_dot;

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
 * @brief Checks for an array of strings, if each one of the strings it 
 * contains, is a valid representation of a number.
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
*	@brief Checks the r, g, b values of the color and accepts only integer 
*	values in the range [0-255]. Rejects negative numbers or floats and 
*	protects from overflow in ft_atoi.
*	@param color_arr: the array of the three strings for the r,g,b values.
*	@returns true: if the the three r,g,b values do NOT meet the requirements
*	for	valid color.
*/
bool	invalid_color(char **color_arr)
{
	int	i;
	int	tmp;

	i = -1;
	while (++i < 3)
	{
		if (ft_strchr(color_arr[i], '.') || color_arr[i][0] == '-')
			return (true);
		tmp = ft_atoi(color_arr[i]);
		if (tmp < 0 || tmp > 255)
			return (true);
	}
	return (false);
}
