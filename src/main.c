/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:59:34 by fvoicu            #+#    #+#             */
/*   Updated: 2024/05/23 20:49:37 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>

void cpuid(uint32_t eax, uint32_t ecx, uint32_t *regs) {
	__asm__ __volatile__(
		"cpuid"
		: "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
		: "a" (eax), "c" (ecx)
	);
}

int main() {
	uint32_t regs[4];
	cpuid(1, 0, regs);

	if (regs[2] & (1 << 28))
		printf("AVX supported\n");
	cpuid(7, 0, regs);
	if (regs[1] & (1 << 5))
		printf("AVX2 supported\n");
	if (regs[1] & (1 << 16))
		printf("AVX-512F supported\n");
	if (regs[1] & (1 << 17))
		printf("AVX-512DQ supported\n");
	if (regs[1] & (1 << 18))
		printf("AVX-512IFMA supported\n");
	if (regs[1] & (1 << 21))
		printf("AVX-512VL supported\n");
	if (regs[1] & (1 << 26))
		printf("AVX-512BW supported\n");
	if (regs[1] & (1 << 27))
		printf("AVX-512VL supported\n");
	return 0;
}
