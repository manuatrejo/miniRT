/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_pdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:10:36 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 15:04:16 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_real	ggx_pdf(t_dir n, t_dir wo, t_dir wi, t_real roughness)
{
	t_dir	h;
	t_real	nh;
	t_real	vh;

	h = vec_normalize(vec_add(wo, wi));
	nh = fmax(dot_product(n, h), (t_real)0.0);
	vh = fmax(dot_product(wo, h), (t_real)0.0);
	if (nh <= (t_real)0.0 || vh <= (t_real)0.0)
		return ((t_real)0.0);
	return (distribution_ggx(nh, roughness) * nh
		/ ((t_real)4.0 * vh + (t_real)1e-4));
}

t_real	spec_probability(t_color f0)
{
	t_real	p;

	p = fmax(f0.x, fmax(f0.y, f0.z));
	return (clamp_real(p, (t_real)0.05, (t_real)0.95));
}

t_real	sample_mixed_brdf(t_hit hit, t_dir dir, t_dir *wi,
	t_color *f)
{
	t_dir	wo;
	t_real	pdf;
	t_real	p_spec;
	t_real	cos_n;
	t_rng	rng;

	wo = dir;
	rng = init_rng((int)hit.p.x, (int)hit.p.z);
	p_spec = spec_probability(f0_from_hit(hit));
	*wi = sample_brdf_dir(hit, wo, p_spec, &rng);
	cos_n = fmax(dot_product(hit.n, *wi), (t_real)0.0);
	if (cos_n <= (t_real)0.0)
	{
		*f = (t_color){0.0, 0.0, 0.0};
		return ((t_real)0.0);
	}
	*f = brdf_eval(hit, hit.n, wo, *wi);
	pdf = p_spec * ggx_pdf(hit.n, wo, *wi, hit.roughness);
	return (pdf + ((t_real)1.0 - p_spec) * (cos_n / M_PI));
}
