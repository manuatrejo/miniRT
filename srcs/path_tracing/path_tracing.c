/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:37:49 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/07 17:47:41 by maanguit         ###   ########.fr       */
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

static bool	miss_step(t_scene *scene, t_pt_state *st)
{
	st->l = vec_add(st->l, vec_prod(st->beta, ambient_radiance(scene)));
	return (false);
}

static void	update_beta(t_pt_state *st, t_color f, t_real cos_n, t_real pdf)
{
	t_real	w;

	if (pdf <= (t_real)0.0)
	{
		st->beta = (t_color){0.0, 0.0, 0.0};
		return ;
	}
	if (pdf < (t_real)1e-6)
		pdf = (t_real)1e-6;
	w = cos_n / pdf;
	st->beta = vec_prod(st->beta, vec_x_scalar(f, w));
}

static bool	path_step(t_scene *scene, t_pt_state *st)
{
	t_bsdf	s;
	t_hit	hit;
	t_dir	wo;
	t_real	pdf;

	hit = get_closest_hit(st->ray, scene);
	if (hit.t >= INFINITE)
		return (miss_step(scene, st));
	if (dot_product(hit.n, st->ray.dir) > (t_real)0.0)
		hit.n = vec_x_scalar(hit.n, (t_real) - 1.0);
	wo = vec_x_scalar(st->ray.dir, (t_real)-1.0);
	if (scene->n_lights > 0)
		st->l = vec_add(st->l, vec_prod(st->beta,
					direct_light(scene, hit, wo)));
	s = sample_mixed_brdf(hit, wo, st->rng);
	pdf = s.pdf;
	update_beta(st, s.f, fmax(dot_product(hit.n, s.wi), (t_real)0.0), pdf);
	st->ray.orig = vec_add(hit.p, vec_x_scalar(hit.n, (t_real)1e-3));
	st->ray.dir = s.wi;
	return (true);
}

t_color	trace_path(t_ray ray, t_scene *scene, t_rng *rng)
{
	t_pt_state	st;
	int			i;

	i = 0;
	st.ray = ray;
	st.l = (t_color){0.0, 0.0, 0.0};
	st.beta = (t_color){1.0, 1.0, 1.0};
	st.rng = rng;
	while (i++ < MAX_DEPTH)
	{
		if (!path_step(scene, &st))
			break ;
		if (i > 2 && !russian_roulette(&st.beta, rng))
			break ;
	}
	return (st.l);
}
