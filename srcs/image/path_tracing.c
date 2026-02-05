/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:37:49 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/05 12:51:15 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	russian_roulette(t_color *beta, t_rng *rng)
{
	t_real	q;
	q = fmax(beta->x, fmax(beta->y, beta->z));
	if (q < (t_real)0.05)
		q = (t_real)0.05;
	if (q > (t_real)1.0)
		q = (t_real)1.0;
	if (rand01(rng) > q)
		return (false);
	*beta = vec_div(*beta, q);
	return (true);
}

static bool	beta_dead(t_color beta)
{
	if (beta.x < (t_real)1e-3
		&& beta.y < (t_real)1e-3
		&& beta.z < (t_real)1e-3)
		return (true);
	return (false);
}

static t_dir	get_tangent(t_dir n)
{
	if (double_abs(n.x) > 0.9)
		return (vec_normalize(vec_cross_prod((t_dir){0.0, 1.0, 0.0}, n)));
	return (vec_normalize(vec_cross_prod((t_dir){1.0, 0.0, 0.0}, n)));
}

static t_dir	sample_cosine_hemisphere(t_dir n, t_rng *rng)
{
	t_dir	t;
	t_dir	b;
	t_real	r1;
	t_real	r2;
	t_real	phi;
	t_real	x;
	t_real	y;
	t_real	z;
	t = get_tangent(n);
	b = vec_cross_prod(n, t);
	r1 = rand01(rng);
	r2 = rand01(rng);
	phi = (t_real)2.0 * M_PI * r1;
	x = cos(phi) * t_real_sqrt(r2);
	y = sin(phi) * t_real_sqrt(r2);
	z = t_real_sqrt((t_real)1.0 - r2);
	return (vec_add(vec_add(vec_x_scalar(t, x),
				vec_x_scalar(b, y)), vec_x_scalar(n, z)));
}

static t_real	clamp_real(t_real v, t_real min, t_real max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

static t_dir	reflect_dir(t_dir v, t_dir n)
{
	return (vec_sub(v, vec_x_scalar(n, (t_real)2.0 * dot_product(v, n))));
}

static t_color	f0_from_hit(t_hit hit)
{
	t_color	base;

	base = vec_x_scalar((t_color){0.04, 0.04, 0.04},
			(t_real)1.0 - hit.metallic);
	return (vec_add(base, vec_x_scalar(hit.albedo, hit.metallic)));
}

static t_color	fresnel_schlick(t_real theta, t_color f0)
{
	t_real	t;
	t_real	one;

	theta = clamp_real(theta, (t_real)0.0, (t_real)1.0);
	one = (t_real)1.0 - theta;
	t = one * one * one * one * one;
	return (vec_add(f0, vec_prod(vec_sub((t_color){1.0, 1.0, 1.0}, f0),
				(t_color){t, t, t})));
}

static t_real	distribution_ggx(t_real nh, t_real roughness)
{
	t_real	a;
	t_real	b;
	t_real	d;

	nh = fmax(nh, (t_real)0.0);
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

static t_real	geometry_smith(t_real nv, t_real nl, t_real roughness)
{
	return (geometry_schlick_ggx(nv, roughness)
		* geometry_schlick_ggx(nl, roughness));
}

static t_dir	sample_ggx_half(t_dir n, t_real roughness, t_rng *rng)
{
	t_dir	t;
	t_dir	b;
	t_real	r1;
	t_real	r2;
	t_real	a;
	t_real	a2;
	t_real	phi;
	t_real	cos_t;
	t_real	sin_t;
	t = get_tangent(n);
	b = vec_cross_prod(n, t);
	r1 = rand01(rng);
	r2 = rand01(rng);
	a = roughness * roughness;
	a2 = a * a;
	phi = (t_real)2.0 * M_PI * r1;
	cos_t = t_real_sqrt(((t_real)1.0 - r2)
			/ ((t_real)1.0 + (a2 - (t_real)1.0) * r2));
	sin_t = t_real_sqrt((t_real)1.0 - cos_t * cos_t);
	return (vec_add(vec_add(vec_x_scalar(t, cos(phi) * sin_t),
				vec_x_scalar(b, sin(phi) * sin_t)),
			vec_x_scalar(n, cos_t)));
}

static t_dir	sample_ggx_reflection(t_dir n, t_dir wo, t_real roughness,
	t_rng *rng)
{
	t_dir	h;

	h = sample_ggx_half(n, roughness, rng);
	if (dot_product(wo, h) < (t_real)0.0)
		h = vec_x_scalar(h, (t_real)-1.0);
	return (reflect_dir(vec_x_scalar(wo, (t_real)-1.0), h));
}

static t_color	specular_term(t_hit hit, t_color f, t_real nv, t_real nl,
	t_real nh)
{
	t_real	d;
	t_real	g;
	t_real	denom;

	d = distribution_ggx(nh, hit.roughness);
	g = geometry_smith(nv, nl, hit.roughness);
	denom = (t_real)4.0 * nv * nl + (t_real)1e-4;
	return (vec_x_scalar(f, d * g / denom));
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

static t_color	brdf_eval(t_hit hit, t_dir n, t_dir wo, t_dir wi)
{
	t_dir	h;
	t_color	f0;
	t_color	f;
	t_real	nl;
	t_real	nv;
	t_real	nh;
	t_real	vh;

	nl = fmax(dot_product(n, wi), (t_real)0.0);
	nv = fmax(dot_product(n, wo), (t_real)0.0);
	if (nl <= (t_real)0.0 || nv <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	h = vec_normalize(vec_add(wo, wi));
	nh = fmax(dot_product(n, h), (t_real)0.0);
	vh = fmax(dot_product(wo, h), (t_real)0.0);
	f0 = f0_from_hit(hit);
	f = fresnel_schlick(vh, f0);
	return (vec_add(diffuse_term(hit, f), specular_term(hit, f, nv, nl, nh)));
}

static t_real	ggx_pdf(t_dir n, t_dir wo, t_dir wi, t_real roughness)
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

static t_real	spec_probability(t_color f0)
{
	t_real	p;

	p = fmax(f0.x, fmax(f0.y, f0.z));
	return (clamp_real(p, (t_real)0.05, (t_real)0.95));
}

static t_dir	sample_brdf_dir(t_hit hit, t_dir wo, t_real p_spec, t_rng *rng)
{
	if (rand01(rng) < p_spec)
		return (sample_ggx_reflection(hit.n, wo, hit.roughness, rng));
	return (sample_cosine_hemisphere(hit.n, rng));
}

static void	sample_mixed_brdf(t_hit hit, t_dir dir, t_rng *rng, t_dir *wi,
	t_color *f, t_real *pdf)
{
	t_dir	wo;
	t_real	p_spec;
	t_real	cos_n;

	wo = dir;
	p_spec = spec_probability(f0_from_hit(hit));
	*wi = sample_brdf_dir(hit, wo, p_spec, rng);
	cos_n = fmax(dot_product(hit.n, *wi), (t_real)0.0);
	if (cos_n <= (t_real)0.0)
	{
		*f = (t_color){0.0, 0.0, 0.0};
		*pdf = (t_real)0.0;
		return ;
	}
	*f = brdf_eval(hit, hit.n, wo, *wi);
	*pdf = p_spec * ggx_pdf(hit.n, wo, *wi, hit.roughness);
	*pdf = *pdf + ((t_real)1.0 - p_spec) * (cos_n / M_PI);
}

static t_color	ambient_radiance(t_scene *scene)
{
	if (!scene->a_light.defined)
		return ((t_color){0.0, 0.0, 0.0});
	return (vec_x_scalar(scene->a_light.color,
			scene->a_light.intensity * (t_real)255.0));
}

static bool	miss_step(t_scene *scene, t_color *beta, t_color *l)
{
	*l = vec_add(*l, vec_prod(*beta, ambient_radiance(scene)));
	return (false);
}

static bool	in_shadow(t_scene *scene, t_hit hit, t_dir ldir, t_real dist)
{
	t_ray	shadow;
	t_hit	occ;
	shadow.orig = vec_add(hit.p, vec_x_scalar(hit.n, (t_real)1e-4));
	shadow.dir = ldir;
	occ = get_closest_hit(shadow, scene);
	if (occ.t < dist - (t_real)1e-4)
		return (true);
	return (false);
}

static t_color	direct_light(t_scene *scene, t_hit hit, t_dir wo)
{
	t_dir	ldir;
	t_real	dist;
	t_real	nl;
	t_color	radiance;

	if (!scene->light.defined)
		return ((t_color){0.0, 0.0, 0.0});
	ldir = vec_sub(scene->light.point, hit.p);
	dist = vec_length(ldir);
	if (dist <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	ldir = vec_div(ldir, dist);
	nl = fmax(dot_product(hit.n, ldir), (t_real)0.0);
	if (nl <= (t_real)0.0)
		return ((t_color){0.0, 0.0, 0.0});
	if (in_shadow(scene, hit, ldir, dist))
		return ((t_color){0.0, 0.0, 0.0});
	radiance = vec_x_scalar(scene->light.color,
			scene->light.intensity * (t_real)255.0);
	return (vec_x_scalar(vec_prod(brdf_eval(hit, hit.n, wo, ldir),
				radiance), nl));
}

static void	update_beta(t_color *beta, t_color f, t_real cos_n, t_real pdf)
{
	t_real	w;
	if (pdf <= (t_real)0.0)
	{
		*beta = (t_color){0.0, 0.0, 0.0};
		return ;
	}
	w = cos_n / pdf;
	*beta = vec_prod(*beta, vec_x_scalar(f, w));
}

static bool	path_step(t_scene *scene, t_rng *rng, t_ray *ray, t_color *beta,
	t_color *l)
{
	t_hit	hit;
	t_dir	wi;
	t_dir	wo;
	t_color	f;
	t_real	pdf;
	t_real	cos_n;
	hit = get_closest_hit(*ray, scene);
	if (hit.t >= INFINITE)
		return (miss_step(scene, beta, l));
	if (dot_product(hit.n, ray->dir) > (t_real)0.0)
		hit.n = vec_x_scalar(hit.n, (t_real)-1.0);
	wo = vec_x_scalar(ray->dir, (t_real)-1.0);
	if (scene->light.defined)
		*l = vec_add(*l, vec_prod(*beta, direct_light(scene, hit, wo)));
	sample_mixed_brdf(hit, wo, rng, &wi, &f, &pdf);
	cos_n = fmax(dot_product(hit.n, wi), (t_real)0.0);
	update_beta(beta, f, cos_n, pdf);
	if (beta_dead(*beta))
		return (false);
	ray->orig = vec_add(hit.p, vec_x_scalar(hit.n, (t_real)1e-4));
	ray->dir = wi;
	return (true);
}

t_color	trace_path(t_ray ray, t_scene *scene, t_rng *rng)
{
	t_color	l;
	t_color	beta;
	int		i;
	i = 0;
	l = (t_color){0.0, 0.0, 0.0};
	beta = (t_color){1.0, 1.0, 1.0};
	while (i++ < MAX_DEPTH)
	{
		if (!path_step(scene, rng, &ray, &beta, &l))
			break ;
		if (i > 2 && !russian_roulette(&beta, rng))
			break ;
	}
	return (l);
}
