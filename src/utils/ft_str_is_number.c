/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:42:41 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/11 17:08:21 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
*	returns true in strings like: 1,  2.0405 235
*	returns false in strings like:
*	0..2452
*	.352
*	++141
*/
bool	ft_str_is_number(const char *str)
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
