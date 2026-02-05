/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   samples.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 08:56:00 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/05 11:05:44 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rng	init_rng(int x, int y)
{
	t_rng	rng;
	__uint32_t	seed;

	seed = 0;
	seed ^= x * 1973;
	seed ^= y * 9277;
	seed |= 1;
	rng.state = seed;
	return (rng);
}

static __uint32_t rng_u32(t_rng *rng)
{
    __uint32_t	x;

	x = rng->state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng->state = x;
    return (x);
}

float	rand01(t_rng *rng)//genera un número aleatorio del 0 al 1
{
    return (rng_u32(rng) >> 8) * (1.0f / 16777216.0f);
}
