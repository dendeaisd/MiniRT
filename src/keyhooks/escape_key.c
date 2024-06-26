/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mevangel <mevangel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:21:20 by mevangel          #+#    #+#             */
/*   Updated: 2024/06/26 15:21:36 by mevangel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	escape(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*mini_rt;

	if (keydata.action != MLX_PRESS)
		return ;
	mini_rt = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_and_exit(1, NULL, mini_rt);
}
