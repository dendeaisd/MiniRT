/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 06:19:10 by fvoicu            #+#    #+#             */
/*   Updated: 2024/06/23 02:17:02 by fvoicu           ###   ########.fr       */
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
	result.x = _mm256_cvtss_f32(res);
	result.y = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 1)));
	result.z = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (result);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	result;
	__m256	vec_a;
	__m256	vec_b;
	__m256	res;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	vec_b = _mm256_set_ps(0, 0, 0, 0, 0, b.z, b.y, b.x);
	res = _mm256_sub_ps(vec_a, vec_b);
	result.x = _mm256_cvtss_f32(res);
	result.y = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 1)));
	result.z = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (result);
}

t_vec	vec_mul(t_vec a, float scalar)
{
	t_vec	result;
	__m256	vec_a;
	__m256	scalar_v;
	__m256	res;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	scalar_v = _mm256_set1_ps(scalar);
	res = _mm256_mul_ps(vec_a, scalar_v);
	result.x = _mm256_cvtss_f32(res);
	result.y = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 1)));
	result.z = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (result);
}

t_vec	vec_div(t_vec a, float scalar)
{
	t_vec	result;
	__m256	vec_a;
	__m256	scalar_v;
	__m256	res;

	vec_a = _mm256_set_ps(0, 0, 0, 0, 0, a.z, a.y, a.x);
	scalar_v = _mm256_set1_ps(scalar);
	res = _mm256_div_ps(vec_a, scalar_v);
	result.x = _mm256_cvtss_f32(res);
	result.y = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 1)));
	result.z = _mm256_cvtss_f32(_mm256_permute_ps \
						(res, _MM_SHUFFLE(0, 0, 0, 2)));
	return (result);
}

float	vec_len(t_vec v)
{
	float	result;
	__m256	vec_v;
	__m256	v_squared;
	__m128	sum;

	vec_v = _mm256_set_ps(0, 0, 0, 0, 0, v.z, v.y, v.x);
	v_squared = _mm256_mul_ps(vec_v, vec_v);
	sum = _mm_add_ps(_mm256_castps256_ps128(v_squared), \
							_mm256_extractf128_ps(v_squared, 1));
	sum = _mm_add_ps(sum, _mm_movehdup_ps(sum));
	sum = _mm_add_ss(sum, _mm_movehl_ps(sum, sum));
	result = _mm_cvtss_f32(sum);
	return (sqrtf(result));
}
