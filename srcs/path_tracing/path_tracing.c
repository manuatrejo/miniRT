/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 06:37:49 by maanguit          #+#    #+#             */
/*   Updated: 2026/02/06 15:05:11 by maanguit         ###   ########.fr       */
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

static bool	miss_step(t_scene *scene, t_color *beta, t_color *l)
{
	*l = vec_add(*l, vec_prod(*beta, ambient_radiance(scene)));
	return (false);
}

static void	update_beta(t_color *beta, t_color f, t_real cos_n, t_real pdf)
{
	t_real	w;

	if (pdf <= (t_real)0.0)
	{
		*beta = (t_color){0.0, 0.0, 0.0};
		return ;
	}
	if (pdf < (t_real)1e-6)
		pdf = (t_real)1e-6;
	w = cos_n / pdf;
	*beta = vec_prod(*beta, vec_x_scalar(f, w));
}

static bool	path_step(t_scene *scene, t_ray *ray, t_color *beta, t_color *l)
{
	t_hit	hit;
	t_dir	wi;
	t_dir	wo;
	t_color	f;
	t_real	pdf;

	hit = get_closest_hit(*ray, scene);
	if (hit.t >= INFINITE)
		return (miss_step(scene, beta, l));
	if (dot_product(hit.n, ray->dir) > (t_real)0.0)
		hit.n = vec_x_scalar(hit.n, (t_real) - 1.0);
	wo = vec_x_scalar(ray->dir, (t_real)-1.0);
	if (scene->light.defined)
		*l = vec_add(*l, vec_prod(*beta, direct_light(scene, hit, wo)));
	pdf = sample_mixed_brdf(hit, wo, &wi, &f);
	update_beta(beta, f, fmax(dot_product(hit.n, wi), (t_real)0.0), pdf);
	ray->orig = vec_add(hit.p, vec_x_scalar(hit.n, (t_real)1e-3));
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
		if (!path_step(scene, &ray, &beta, &l))
			break ;
		if (i > 2 && !russian_roulette(&beta, rng))
			break ;
	}
	return (l);
}
