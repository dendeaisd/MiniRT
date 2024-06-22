/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:19:10 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/22 06:51:48 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/vec3.h"
#include <immintrin.h> 

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	result;
	__m256	vec_a;
	__m256	vec_b;
	__m256	res;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	vec_b = _mm256_set_ps(0, 0, 0, 0, 0, b.z, b.y, b.x);
	res = _mm256_add_ps(vec_a, vec_b);
	//cvts-> extracts lowest elem from res ==> a.x + b.x
	result.x = _mm256_cvtss_f32(res);
	//mm_shuffle-> move 2nd elem to the lowest position
	result.y = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 1)));
	//mm_shuffle-> move 3nd elem to the lowest position
	result.z = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (result);
}
