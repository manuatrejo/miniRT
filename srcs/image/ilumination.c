/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilumination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:21:19 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/05 08:05:34 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	fresnel_schlick(t_real theta, t_vec3 f0)
{
	t_real	t;

	theta = fmin(fmax(theta, 0.0), 1.0);
	t = (t_real)pow((t_real)1.0 - theta, (t_real)5.0);
	return (vec_add(f0, vec_prod(vec_sub((t_vec3){1.0, 1.0, 1.0}, f0),
		(t_vec3){t, t, t})));
}

t_real	distribution_ggx(t_real nh, t_real roughness)
{
	t_real	a;
	t_real	b;
	t_real	d;

	nh = fmax(nh, 0.0);
	a = roughness * roughness;
	b = a * a;
	d = (nh * nh) * (b - 1.0) + 1.0;
	return (b / (M_PI * d * d + 1e-4));
}

t_real geometry_schlick_ggx(t_real nx, t_real roughness)
{
	t_real	r;
	t_real	k;

	r = roughness + 1.0;
	k = (r * r) / 8.0;
	return (nx / (nx * (1.0 - k) + k + 1e-4));
}

t_real geometry_smith(t_real nv, t_real nl, t_real roughness)
{
	t_real	gv;
	t_real	gl;

	gv = geometry_schlick_ggx(nv, roughness);
	gl = geometry_schlick_ggx(nl, roughness);
	return (gv * gl);
}
/*
Convertir a GGX BRDF
*/
t_color	cook_torrance(t_hit	*hit, t_light l, t_dir view)
{
	t_color color;
	t_ct	ct;

	ct.l_c = vec_normalize(vec_sub(l.point, hit->p));
	ct.h = vec_normalize(vec_add(view, ct.l_c));
	if (dot_product(hit->n, view) < 0.0)
    	hit->n = vec_x_scalar(hit->n, (t_real)-1.0);
	ct.nl = fmax(dot_product(hit->n, ct.l_c), 0.0);
	ct.nv = fmax(dot_product(hit->n, view), 0.0);
	ct.nh = fmax(dot_product(hit->n, ct.h), 0.0);
	ct.vh = fmax(dot_product(view, ct.h), 0.0);
	if (ct.nl <= 0.0 || ct.nv <= 0.0)
		return ((t_color){0.0, 0.0, 0.0});
	ct.f0 = vec_add(vec_x_scalar((t_vec3){0.04, 0.04, 0.04}, 1.0 - hit->metallic),
		vec_x_scalar(hit->albedo, hit->metallic));
	ct.f = fresnel_schlick(ct.vh, ct.f0);
	ct.d = distribution_ggx(ct.nh, hit->roughness);
	ct.g = geometry_smith(ct.nv, ct.nl, hit->roughness);
	ct.res = ct.d * ct.g / (4.0 * ct.nv * ct.nl + 1e-4);
	//añadir ambient (BUSCAR COMO METER AMBIENT_L)
	ct.specular = vec_prod(ct.f, (t_vec3){ct.res, ct.res, ct.res});
	ct.kd = vec_prod(vec_sub((t_dir){1.0, 1.0, 1.0}, ct.f),
		(t_vec3){1.0 - hit->metallic, 1.0 - hit->metallic, 1.0 - hit->metallic});
	ct.diffuse = vec_x_scalar(hit->albedo, 1.0 / M_PI);
	ct.diffuse = vec_prod(ct.diffuse, ct.kd);
	ct.radiance = vec_x_scalar(l.color, l.intensity * 255);
    color = vec_prod(vec_add(ct.diffuse, ct.specular), ct.radiance);
    return (vec_x_scalar(color, ct.nl * 3));
}
