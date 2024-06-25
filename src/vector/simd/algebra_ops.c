/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:09:13 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/24 01:30:54 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec3.h"

float	vec_dot(t_vec a, t_vec b)
{
	__m256	vec_a;
	__m256	vec_b;
	__m256	vec_mul;
	__m128	sum;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	vec_b = _mm256_set_ps(0, 0, 0, 0, 0, b.z, b.y, b.x);
	vec_mul = _mm256_mul_ps(vec_a, vec_b);
	sum = _mm_add_ps(_mm256_castps256_ps128(vec_mul), \
					_mm256_extractf128_ps(vec_mul, 1));
	sum = _mm_add_ps(sum, _mm_movehdup_ps(sum));
	sum = _mm_add_ss(sum, _mm_movehl_ps(sum, sum));
	return (_mm_cvtss_f32(sum));
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	res;
	__m256	vec_a;
	__m256	vec_b;
	__m256	mul1;
	__m256	sub;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.x, a.z, a.y);
	vec_b = _mm256_set_ps(0, 0, 0, 0, 0, b.y, b.x, b.z);
	mul1 = _mm256_mul_ps(vec_a, vec_b);
	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.y, a.x, a.z);
	vec_b = _mm256_set_ps(0, 0, 0, 0, 0, b.x, b.z, b.y);
	sub = _mm256_sub_ps(mul1, _mm256_mul_ps(vec_a, vec_b));
	res.x = _mm256_cvtss_f32(_mm256_permute_ps(sub, _MM_SHUFFLE(0, 0, 0, 0)));
	res.y = _mm256_cvtss_f32(_mm256_permute_ps(sub, _MM_SHUFFLE(0, 0, 0, 1)));
	res.z = _mm256_cvtss_f32(_mm256_permute_ps(sub, _MM_SHUFFLE(0, 0, 0, 2)));
	return (res);
}

t_vec	vec_unit(t_vec a)
{
	float	length;
	__m256	vec_a;
	__m256	vec_leng;
	__m256	vec_res;
	t_vec	res;

	length = vec_len(a);
	if (length == 0)
		return ((t_vec){0.f, 0.f, 0.f});
	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	vec_leng = _mm256_set1_ps(length);
	vec_res = _mm256_div_ps(vec_a, vec_leng);
	res.x = _mm256_cvtss_f32(vec_res);
	res.y = _mm256_cvtss_f32(_mm256_permute_ps \
					(vec_res, _MM_SHUFFLE(0, 0, 0, 1)));
	res.z = _mm256_cvtss_f32(_mm256_permute_ps \
					(vec_res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (res);
}
