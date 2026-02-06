/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdrf_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:21:19 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 15:02:43 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	fresnel_schlick(t_real theta, t_vec3 f0)
{
	t_real	t;
	t_real	one;

	theta = clamp_real(theta, (t_real)0.0, (t_real)1.0);
	one = (t_real)1.0 - theta;
	t = one * one * one * one * one;
	return (vec_add(f0, vec_prod(vec_sub((t_color){1.0, 1.0, 1.0}, f0),
			(t_color){t, t, t})));
}

t_real	distribution_ggx(t_real nh, t_real roughness)
{
	t_real	a;
	t_real	b;
	t_real	d;

	nh = fmax(nh, 0.0);
	a = roughness * roughness;
	b = a * a;
	d = (nh * nh) * (b - (t_real)1.0) + (t_real)1.0;
	return (b / (M_PI * d * d + (t_real)1e-4));
}

static t_real	geometry_schlick_ggx(t_real nx, t_real roughness)
{
	t_real	r;
	t_real	k;

	r = roughness + (t_real)1.0;
	k = (r * r) / (t_real)8.0;
	return (nx / (nx * ((t_real)1.0 - k) + k + (t_real)1e-4));
}

t_real	geometry_smith(t_real nv, t_real nl, t_real roughness)
{
	return (geometry_schlick_ggx(nv, roughness)
		* geometry_schlick_ggx(nl, roughness));
}
