/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:57:14 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/11 19:25:57 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		++(*str);
	}
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	result;

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

double	ft_atof(const char *str)
{
	double	sign;
	double	fraction;
	double	result;

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
