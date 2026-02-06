/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_brdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:10:09 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 12:10:17 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_dir	reflect_dir(t_dir v, t_dir n)
{
	return (vec_sub(v, vec_x_scalar(n, (t_real)2.0 * dot_product(v, n))));
}

t_color	f0_from_hit(t_hit hit)
{
	t_color	base;

	base = vec_x_scalar((t_color){0.04, 0.04, 0.04},
			(t_real)1.0 - hit.metallic);
	return (vec_add(base, vec_x_scalar(hit.albedo, hit.metallic)));
}

static t_real	specular_term(t_hit hit, t_real nv, t_real nl, t_real nh)
{
	t_real	d;
	t_real	g;
	t_real	denom;

	d = distribution_ggx(nh, hit.roughness);
	g = geometry_smith(nv, nl, hit.roughness);
	denom = (t_real)4.0 * nv * nl + (t_real)1e-4;
	return (d * g / denom);
}

static t_color	diffuse_term(t_hit hit, t_color f)
{
	t_color	kd;
	t_color	diff;

	kd = vec_prod(vec_sub((t_color){1.0, 1.0, 1.0}, f),
			(t_color){(t_real)1.0 - hit.metallic,
			(t_real)1.0 - hit.metallic,
			(t_real)1.0 - hit.metallic});
	diff = vec_x_scalar(hit.albedo, (t_real)1.0 / M_PI);
	return (vec_prod(diff, kd));
}

t_color	brdf_eval(t_hit hit, t_dir n, t_dir wo, t_dir wi)
{
	t_dir	h;
	t_color	f;
	t_real	nl;
	t_real	nv;
	t_real	nh;

	nl = fmax(dot_product(n, wi), (t_real)0.0);
	nv = fmax(dot_product(n, wo), (t_real)0.0);
	if (nl <= (t_real)0.0 || nv <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	h = vec_normalize(vec_add(wo, wi));
	nh = fmax(dot_product(n, h), (t_real)0.0);
	f = fresnel_schlick(fmax(dot_product(wo, h), (t_real)0.0),
			f0_from_hit(hit));
	return (vec_add(diffuse_term(hit, f),
			vec_x_scalar(f, specular_term(hit, nv, nl, nh))));
}
