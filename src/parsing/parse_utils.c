/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:35:19 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/14 15:57:03 by mevangel         ###   ########.fr       */
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

void	ft_exit_miniRT(char *err_msg, int exit_value, char **array_to_free, t_mini_rt *mini_RT)
{
	if (err_msg)
	{
		ft_putstr_fd(ERROR, 2);
		ft_putendl_fd(err_msg, 2);
	}
	if (array_to_free)
		fv_free_array(array_to_free);
	if (mini_RT)
	{
		fv_free_array(mini_RT->parser.map_2d);
		free(mini_RT->scene.objects);
	}
	if (exit_value == 1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
