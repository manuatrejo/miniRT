/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   samples.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 08:56:00 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 10:12:47 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rng	init_rng(int x, int y)
{
	t_rng	seed;

	seed = 0;
	seed ^= x * 1973;
	seed ^= y * 9277;
	seed |= 1;
	return (seed);
}

static t_rng	rng_u32(t_rng *rng)
{
	unsigned int	x;

	x = *rng;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*rng = x;
	return (x);
}

float	rand01(t_rng *rng)
{
	return ((rng_u32(rng) >> 8) * (1.0f / 16777216.0f));
}
