/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_sampling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:09:42 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 14:41:28 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_dir	get_tangent(t_dir n)
{
	if (double_abs(n.x) > 0.9)
		return (vec_normalize(vec_cross_prod((t_dir){0.0, 1.0, 0.0}, n)));
	return (vec_normalize(vec_cross_prod((t_dir){1.0, 0.0, 0.0}, n)));
}

static t_dir	sample_cosine_hemisphere(t_dir n, t_rng *rng)
{
	t_dir	t;
	t_real	r;
	t_real	phi;
	t_real	y;
	t_real	z;

	t = get_tangent(n);
	r = rand01(rng);
	phi = (t_real)2.0 * M_PI * rand01(rng);
	z = t_real_sqrt((t_real)1.0 - r);
	r = t_real_sqrt(r);
	y = sin(phi) * r;
	return (vec_add(vec_add(vec_x_scalar(t, cos(phi) * r),
				vec_x_scalar(vec_cross_prod(n, t), y)), vec_x_scalar(n, z)));
}

static t_dir	sample_ggx_half(t_dir n, t_real roughness, t_rng *rng)
{
	t_dir	t;
	t_real	r;
	t_real	a2;
	t_real	phi;
	t_real	cos_sin[2];

	t = get_tangent(n);
	r = rand01(rng);
	a2 = roughness * roughness;
	a2 = a2 * a2;
	phi = (t_real)2.0 * M_PI * rand01(rng);
	cos_sin[0] = t_real_sqrt(((t_real)1.0 - r)
			/ ((t_real)1.0 + (a2 - (t_real)1.0) * r));
	cos_sin[1] = t_real_sqrt((t_real)1.0 - cos_sin[0] * cos_sin[0]);
	return (vec_add(vec_add(vec_x_scalar(t, cos(phi) * cos_sin[1]),
				vec_x_scalar(vec_cross_prod(n, t), sin(phi) * cos_sin[1])),
			vec_x_scalar(n, cos_sin[0])));
}

static t_dir	sample_ggx_reflection(t_dir n, t_dir wo, t_real roughness,
	t_rng *rng)
{
	t_dir	h;

	h = sample_ggx_half(n, roughness, rng);
	if (dot_product(wo, h) < (t_real)0.0)
		h = vec_x_scalar(h, (t_real) - 1.0);
	return (reflect_dir(vec_x_scalar(wo, (t_real) - 1.0), h));
}

t_dir	sample_brdf_dir(t_hit hit, t_dir wo, t_real p_spec, t_rng *rng)
{
	if (rand01(rng) < p_spec)
		return (sample_ggx_reflection(hit.n, wo, hit.roughness, rng));
	return (sample_cosine_hemisphere(hit.n, rng));
}
