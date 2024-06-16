/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:57:14 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/16 16:55:46 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	parse_integer_part(const char **str)
{
	float	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		++(*str);
	}
	return (result);
}

static float	parse_fractional_part(const char **str)
{
	float	fraction;
	float	result;

	fraction = 0.1;
	result = 0.0;
	if (**str == '.')
	{
		++(*str);
		while (**str >= '0' && **str <= '9')
		{
			result += (**str - '0') * fraction;
			fraction *= 0.1;
			++(*str);
		}
	}
	return (result);
}

float	ft_atof(const char *str)
{
	float	sign;
	float	fraction;
	float	result;

	sign = 1.0;
	fraction = 0.1;
	result = 0.0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		++str;
	}
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	return (sign * result);
}
